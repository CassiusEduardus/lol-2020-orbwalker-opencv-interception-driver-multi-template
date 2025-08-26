#include "GetSpaceState.h"

#include "Estruturas.h"

extern KBD_Context_STRUCT KBD_Context;

extern int SPACE_STATE_G;

GetSpaceState::GetSpaceState()
{
    this->getSpaceStateThread = std::thread(&GetSpaceState::GetSpaceST, this);
    this->getSpaceStateThread.detach();
}

void GetSpaceState::GetSpaceST()
{
    KBD_Context.Contexto_Teclado = interception_create_context();

    interception_set_filter(KBD_Context.Contexto_Teclado, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);

    while (interception_receive(KBD_Context.Contexto_Teclado, KBD_Context.DeviceID_Teclado = interception_wait(KBD_Context.Contexto_Teclado), (InterceptionStroke*)&KBD_Context.Keystrok_Teclado, 1) > 0)
    {
        if (KBD_Context.Keystrok_Teclado.code != SCANCODE_SPACE)
        {
            interception_send(KBD_Context.Contexto_Teclado, KBD_Context.DeviceID_Teclado, (InterceptionStroke*)&KBD_Context.Keystrok_Teclado, 1);
        }
        else
        {
            if (KBD_Context.Keystrok_Teclado.code == SCANCODE_SPACE && KBD_Context.Keystrok_Teclado.state == INTERCEPTION_KEY_UP)
            {
                SPACE_STATE_G = 0;
            }

            if (KBD_Context.Keystrok_Teclado.code == SCANCODE_SPACE && KBD_Context.Keystrok_Teclado.state == INTERCEPTION_KEY_DOWN)
            {
                SPACE_STATE_G = 1;
            }
        }
        //c_v.notify_all();
    }
    interception_destroy_context(KBD_Context.Contexto_Teclado);
}

GetSpaceState::~GetSpaceState()
{
    ;
}
