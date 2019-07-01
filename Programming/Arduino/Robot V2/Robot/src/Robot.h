#pragma once

#include "Robot/Utils/Timer.h"
#include "Robot/Utils/Diagnostic.h"
#include "Robot/Hardware/Digital/Button.h"
#include "Robot/Hardware/Digital/DigitalLED.h"
#include "Robot/Hardware/I2C/Accelerometer.h"
#include "Robot/Hardware/I2C/Lightgate.h"
#include "Robot/Hardware/I2C/LightSensorArray.h"
#include "Robot/Hardware/I2C/Magnetometer.h"
#include "Robot/Hardware/I2C/MotorController.h"
#include "Robot/Hardware/I2C/TSOPSensorArray.h"
#include "Robot/Hardware/Serial/Communication.h"


void Init();
void Begin();
void End();
void Run();
void Update();


// -------| Robot Entry Point |-------
#include "Robot/EntryPoint.h"
// -------|===================|-------