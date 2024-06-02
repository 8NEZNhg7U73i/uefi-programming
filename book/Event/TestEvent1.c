#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleTextIn.h>

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
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL                    *SimpleInput;
  SimpleInput = (EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *)Context;
  if (!EFI_ERROR (KeyboardCheckForKey ())) {
    gBS->SignalEvent (SimpleInput->WaitForKey);
  }
}

EFI_STATUS Status;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL                      *SimpleInput;

EFI_STATUS EFIAPI
UefiMain(
        IN EFI_HANDLE           ImageHandle,
        IN EFI_SYSTEM_TABLE     *SystemTable
		)
{

  //
  // Create a wait event for a Simple Input Protocol
  //
  Status = gBS->CreateEvent(
      EVT_NOTIFY_WAIT,               // Type
      TPL_NOTIFY,                    // NotifyTpl
      NotifyKeyboardCheckForKey,     // NotifyFunction
      SimpleInput,                 // NotifyContext
      &(SimpleInput->WaitForKey) // Event
  );
  if (EFI_ERROR(Status))
  {
    Print(L"Status: %r", Status);
    return Status;
  }

  //
  // Close the wait event
  //
  Status = gBS->CloseEvent(SimpleInput->WaitForKey);
  if (EFI_ERROR(Status))
  {
    return Status;
  }
  else
  {
    return Status;
  }
}