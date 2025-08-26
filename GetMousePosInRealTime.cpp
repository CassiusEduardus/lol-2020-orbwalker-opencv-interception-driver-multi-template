#include "GetMousePosInRealTime.h"

extern int SPACE_STATE_G;

extern unsigned int screenWidth;
extern unsigned int screenHeight;

extern MSE_Context_STRUCT MOUSE_CONTEXT_G;

extern InterceptionMouseStroke MOUSE_STROKE_MYPOS;

extern InterceptionMouseStroke MOUSE_STROKE_ENPOS;

point position(screenWidth / 2, screenHeight / 2);

GetMousePosInRealTime::GetMousePosInRealTime()
{
    this->getMousePosThread = std::thread(&GetMousePosInRealTime::GetMousePos, this);
    this->getMousePosThread.detach();
}

void GetMousePosInRealTime::GetMousePos()
{
    MOUSE_CONTEXT_G.Contexto_Mouse = interception_create_context();

    interception_set_filter(MOUSE_CONTEXT_G.Contexto_Mouse, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_MOVE);

    while (interception_receive(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse = interception_wait(MOUSE_CONTEXT_G.Contexto_Mouse), &MOUSE_CONTEXT_G.Stroke_Mo_Mouse, 1) > 0)
    {
        if (interception_is_mouse(MOUSE_CONTEXT_G.DeviceID_Mouse))
        {
            InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&MOUSE_CONTEXT_G.Stroke_Mo_Mouse;

            position.x += mstroke.x;
            position.y += mstroke.y;

            if (position.x < 0)
                position.x = 0;
            if (position.x > screenWidth - 1)
                position.x = screenWidth - 1;
            if (position.y < 0)
                position.y = 0;
            if (position.y > screenHeight - 1)
                position.y = screenHeight - 1;

            mstroke.flags = INTERCEPTION_MOUSE_MOVE_ABSOLUTE;
            mstroke.x = static_cast<int>((0xFFFF * position.x) / screenWidth);
            mstroke.y = static_cast<int>((0xFFFF * position.y) / screenHeight);

            MOUSE_STROKE_MYPOS.x = mstroke.x;
            MOUSE_STROKE_MYPOS.y = mstroke.y;

            if (!SPACE_STATE_G || MOUSE_STROKE_ENPOS.x == 0)
                interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, &MOUSE_CONTEXT_G.Stroke_Mo_Mouse, 1);
        }
    }
}

GetMousePosInRealTime::~GetMousePosInRealTime()
{

}