// /////////////////////////////////////////////////////////////////
// // State machine setup
// /////////////////////////////////////////////////////////////////
// unsigned long timer_duration = 0;
// unsigned long start_millis;

// StateMachine machine = StateMachine();

// // state handlers
// void stateStartHandler() {
//   updateStatus(IDLE, 6000, 0xFFFFFF, bitmap_sleeper);
// }
// void stateWaitHandler() {}
// void stateRequestedHandler() {
//   updateStatus(WAITING, 15000, 0xFFFF00, bitmap_bell);
//   // flush hc12's buffer
//   hc12.flush();
// }
// void stateCheckResponseHandler() {}
// void stateShowStatusCancelledHandler() {
//   updateStatus(CANCELLED, 2000, 0x00FFFF, bitmap_no);
// }
// void stateShowStatusAcceptedHandler() {
//   updateStatus(ACCEPTED, 5000, 0x00FF00, bitmap_yes);
// }
// void stateShowStatusDeniedHandler() {
//   updateStatus(DENIED, 5000, 0xFF0000, bitmap_no);
// }
// void stateRequestReceivedHandler() {
//   updateStatus(WAITING, 15000, 0xFFFF00, bitmap_bell);
// }
// void stateWaitForResponseHandler() {}
// void stateRespondedWithYesHandler() {
//   updateStatus(ACCEPTED, 5000, 0x00FF00, bitmap_yes);
// }
// void stateRespondedWithNoHandler() {
//   updateStatus(DENIED, 5000, 0xFF0000, bitmap_no);
// }

// // create states
// State* SStart = machine.addState(&stateStartHandler);
// State* SWait = machine.addState(&stateWaitHandler);

// State* SRequested = machine.addState(&stateRequestedHandler);
// State* SCheckResponse = machine.addState(&stateCheckResponseHandler);
// State* SShowStatusCancelled = machine.addState(&stateShowStatusCancelledHandler);
// State* SShowStatusAccepted = machine.addState(&stateShowStatusAcceptedHandler);
// State* SShowStatusDenied = machine.addState(&stateShowStatusDeniedHandler);

// State* SRequestReceived = machine.addState(&stateRequestReceivedHandler);
// State* SWaitForResponse = machine.addState(&stateWaitForResponseHandler);
// State* SRespondedWithYes = machine.addState(&stateRespondedWithYesHandler);
// State* SRespondedWithNo = machine.addState(&stateRespondedWithNoHandler);

// // create transition conditions
// bool transitionAlwaysTrue() {
//   return true;
// }
// bool transitionWaitButtonAPressed() {
//   return (digitalRead(BUTTON_A_PIN) == HIGH);
// }
// bool transitionWaitButtonBPressed() {
//   return (digitalRead(BUTTON_B_PIN) == HIGH);
// }
// bool transitionResponseAccepted() {
//   if (hc12.available()) {
//   }
// }
// bool transitionResponseDenied() { /* check response message received */
// }
// bool transitionRequestReceived() { /* check request message received */
// }

// void updateStatus(STATUS status, unsigned long timer_duration, int led_color, const byte* bitmap) {
//   // set LED to led_color

//   // start timer
//   start_millis = millis();

//   // update display
//   display.clearDisplay();
//   display.drawBitmap(32, 0, bitmap, FRAME_WIDTH, FRAME_HEIGHT, 1);
//   display.display();
// }

// void setup() {
//   // display
//   display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);

//   // state machine
//   // set transitions
//   SStart->addTransition(&transitionAlwaysTrue, SWait);  // start -> wait

//   // requester transitions
//   SWait->addTransition(&transitionWaitButtonBPressed, SRequested);   // wait -> requested on button B press
//   SRequested->addTransition(&transitionAlwaysTrue, SCheckResponse);  // requested to check response

//   SCheckResponse->addTransition(&transitionResponseAccepted, SShowStatusAccepted);     // check response -> accepted on message receive
//   SCheckResponse->addTransition(&transitionResponseDenied, SShowStatusDenied);         // check respoinse -> denied on message receive
//   SCheckResponse->addTransition(&transitionWaitButtonAPressed, SShowStatusCancelled);  // check respoinse -> cancelled on button A press

//   SShowStatusAccepted->addTransition(&transitionAlwaysTrue, SWait);   // accepted -> wait
//   SShowStatusDenied->addTransition(&transitionAlwaysTrue, SWait);     // denied -> wait
//   SShowStatusCancelled->addTransition(&transitionAlwaysTrue, SWait);  // cancelled -> wait

//   // responder transitions
//   SWait->addTransition(&transitionRequestReceived, SRequestReceived);        // wait -> request received remotely
//   SRequestReceived->addTransition(&transitionAlwaysTrue, SWaitForResponse);  // request received -> respond with buttons

//   SWaitForResponse->addTransition(&transitionWaitButtonBPressed, SRespondedWithYes);  // wait for button press -> responded with yes on button B
//   SWaitForResponse->addTransition(&transitionWaitButtonAPressed, SRespondedWithNo);   // wait for button press -> responded with no on button A

//   SRespondedWithYes->addTransition(&transitionAlwaysTrue, SWait);  // accepted -> wait
//   SRespondedWithNo->addTransition(&transitionAlwaysTrue, SWait);   // declined -> wait

//   // buttons
//   pinMode(BUTTON_A_PIN, INPUT);
//   pinMode(BUTTON_B_PIN, INPUT);

//   // LED
//   pinMode(LED_PIN, OUTPUT);

//   // HC12
//   hc12.begin(9600);  // Serial port to HC12
// }

// void loop() {

//   machine.run();

//   if (timer_duration == 0) {
//     return;
//   }

//   unsigned long current_millis = millis();
//   if (current_millis - start_millis <= 0) {
//     // idle
//     timer_duration = 0;
//     display.clearDisplay();
//     display.display();
//   }

//   // check messages
// }
