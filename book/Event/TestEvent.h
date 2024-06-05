VOID TimeNotify(IN EFI_EVENT Event, IN VOID *Context);
VOID KeyNotify(IN EFI_EVENT Event, IN VOID *Context);


EFI_SIMPLE_TEXT_INPUT_PROTOCOL                      *SimpleInput;

EFI_INPUT_KEY Key;
EFI_STATUS Status;
UINTN waitidx;
CHAR16 *KeyNotifyContext = L"TimeNotify!";
EFI_EVENT KeyEvent;
EFI_EVENT KeyEvent = gST->ConIn->WaitForKey;

