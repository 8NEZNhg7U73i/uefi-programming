#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleTextInEx.h>

EFI_STATUS
KeyboardCheckForKey (
   VOID
  )
{
  //
  // Perform hardware specific action to detect if a key on a
  // keyboard has been pressed.
  //
  return EFI_SUCCESS;
}

VOID
EFIAPI
NotifyKeyboardCheckForKey (
  IN EFI_EVENT                                         Event,
  IN VOID                                              *Context
  )
{
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL                    *SimpleInputEx;
  SimpleInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *)Context;
  if (!EFI_ERROR (KeyboardCheckForKey ())) {
    gBS->SignalEvent (SimpleInputEx->WaitForKeyEx);
  }
}

EFI_STATUS Status;
EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL                      *SimpleInputEx;

//
// Create a wait event for a Simple Input Protocol
//
Status = gBS->CreateEvent (
                EVT_NOTIFY_WAIT,                       // Type
                TPL_NOTIFY,                            // NotifyTpl
                NotifyKeyboardCheckForKey,             // NotifyFunction
                SimpleInputEx,                         // NotifyContext
                &(SimpleInputEx->WaitForKeyEx)         // Event
                );
if (EFI_ERROR (Status)) {
  return Status;
}

//
// Close the wait event
//
Status = gBS->CloseEvent (SimpleInputEx->WaitForKeyEx);
if (EFI_ERROR (Status)) {
  return Status;
}