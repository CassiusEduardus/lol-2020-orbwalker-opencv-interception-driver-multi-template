#include "GetStatsInRealtime.h"
#include "GetClosestEnemy.h"
#include "GetMousePosInRealTime.h"
#include "GetScreenSize.h"
#include "GetSpaceState.h"
#include "GetCastWalkSleep.h"

extern InterceptionMouseStroke MOUSE_STROKE_ENPOS;
extern InterceptionMouseStroke MOUSE_STROKE_MYPOS;

extern MSE_Context_STRUCT MOUSE_CONTEXT_G;

extern int SPACE_STATE_G;

extern int SLEEP_CAST_G;
extern int SLEEP_WALK_G;

int main()
{
    unsigned int screenResolutionID = 0;

    GetScreenSize getscreensize;

    screenResolutionID = getscreensize.GetScreenResolutionID();

    GetMousePosInRealTime getmousepos;
    
    GetSpaceState getspacestate;

    GetCastWalkSleep getcastwalksleep;

    GetStatsInRealtime getstats(screenResolutionID);

    GetClosestEnemy getclosest(screenResolutionID);

    std::cout << getscreensize.GetScreenResolutionID() << std::endl;

    MOUSE_STROKE_ENPOS.flags = INTERCEPTION_MOUSE_MOVE_ABSOLUTE;
    MOUSE_STROKE_MYPOS.flags = INTERCEPTION_MOUSE_MOVE_ABSOLUTE;

    while (TRUE)
    {
        while (SPACE_STATE_G)
        {
            if (MOUSE_STROKE_ENPOS.x > 0)
            {
            MOUSE_STROKE_ENPOS.state = INTERCEPTION_MOUSE_BUTTON_3_DOWN;
            interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, (InterceptionStroke*)&MOUSE_STROKE_ENPOS, 1);

            MOUSE_STROKE_ENPOS.state = INTERCEPTION_MOUSE_BUTTON_3_UP;
            interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, (InterceptionStroke*)&MOUSE_STROKE_ENPOS, 1);

            MOUSE_STROKE_ENPOS.state = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN;
            interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, (InterceptionStroke*)&MOUSE_STROKE_ENPOS, 1);

            MOUSE_STROKE_ENPOS.state = INTERCEPTION_MOUSE_LEFT_BUTTON_UP;
            interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, (InterceptionStroke*)&MOUSE_STROKE_ENPOS, 1);

            std::this_thread::sleep_for(std::chrono::milliseconds((SLEEP_CAST_G)));

            MOUSE_STROKE_MYPOS.state = INTERCEPTION_MOUSE_RIGHT_BUTTON_DOWN;
            interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, (InterceptionStroke*)&MOUSE_STROKE_MYPOS, 1);

            MOUSE_STROKE_MYPOS.state = INTERCEPTION_MOUSE_RIGHT_BUTTON_UP;
            interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, (InterceptionStroke*)&MOUSE_STROKE_MYPOS, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds((SLEEP_WALK_G)));
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds((10)));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds((10)));
    }

    return 0;
}
