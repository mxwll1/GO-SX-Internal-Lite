//
//  functions.cpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 15.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "functions.h"

int Functions::MessageBox(const char* header, const char* message, unsigned long message_type)
{
    CFStringRef header_ref = CFStringCreateWithCString(NULL, header, (CFStringEncoding)strlen(header));
    CFStringRef message_ref = CFStringCreateWithCString(NULL, message, (CFStringEncoding)strlen(message));
    CFOptionFlags result;

    CFUserNotificationDisplayAlert(
        0,
        kCFUserNotificationNoteAlertLevel, //change it depending message_type flags ( MB_ICONASTERISK.... etc.)
        NULL,
        NULL,
        NULL,
        header_ref,
        message_ref,
        NULL,
        NULL,
        NULL,
        &result
    );

    CFRelease( header_ref );
    CFRelease( message_ref );

    if (result == kCFUserNotificationDefaultResponse) {
        return IDOK;
    } else {
        return IDCANCEL;
    }
    
}

std::string Functions::GetModulePath(std::string module) {
    return CPatternScanner::Instance()->GetModulePath("gosx.dylib");
}

float Functions::RandomFloat(float minVal, float maxVal)
{
    return minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

bool Functions::IsKeyPressed(unsigned short inKeyCode) {
    unsigned char keyMap[16];
    GetKeys((BigEndianUInt32*) &keyMap);
    return (0 != ((keyMap[ inKeyCode >> 3] >> (inKeyCode & 7)) & 1));
}

void Functions::SetMousePos(int x, int y)
{
    CGPoint pt;
    pt.x = x;
    pt.y = y;

    CGEventRef moveEvent = CGEventCreateMouseEvent(
        NULL,
        kCGEventMouseMoved,
        pt,
        kCGMouseButtonLeft
    );

    CGEventPost(kCGSessionEventTap, moveEvent);
    CFRelease(moveEvent);
}

bool Functions::FileExist(std::string fileName) {
    std::ifstream infile(fileName);
    bool result = infile.good();
    infile.close();
    return result;
}

std::string Functions::DirName(std::string source)
{
    source.erase(find(source.rbegin(), source.rend(), '/').base(), source.end());
    return source;
}
