#pragma once
#include <Windows.h>

#include <vector>
#include "Util/Logger.hpp"
#include "simpleini/SimpleIni.h"

class VehicleConfig;
class Logger;
class CarControls;

enum class EShiftMode : int {
    Sequential = 0,
    HPattern = 1,
    Automatic = 2,
};

EShiftMode Next(EShiftMode mode);

class ScriptSettings {
public:
    ScriptSettings();
    void SetFiles(const std::string &general, const std::string& controls, const std::string &wheel);
    void Read(CarControls* scriptControl);
    void SaveGeneral() const;
    void SaveController(CarControls* scriptControl) const;
    void SaveWheel() const;

    void SetVehicleConfig(VehicleConfig* cfg);
    ScriptSettings operator()();

    struct TimerParams {
        std::string Unit;
        float LimA;
        float LimB;
        float Tolerance;
    };

    // settings_general.ini parts
    // [MT_OPTIONS]
    struct {
        bool Enable = true;
        // 0 Seq, 1 H, 2 Auto
        EShiftMode ShiftMode = EShiftMode::Sequential;
        bool Override = true;

        bool EngDamage = false;
        // H-Pattern
        bool EngStallH = true;
        bool EngStallS = false;
        bool EngBrake = false;
        bool EngLock = false;
        bool ClutchCreep = false;
        bool ClutchShiftH = true;
        bool ClutchShiftS = false;
        bool HardLimiter = true;
    } MTOptions;

    // [MT_PARAMS]
    struct {
        float EngBrakePower = 0.0f;
        float EngBrakeThreshold = 0.75f;
        // Clutch _lift_ distance
        float ClutchThreshold = 0.15f;
        // Clutch _lift_ distance
        float StallingThreshold = 0.35f;
        float StallingRPM = 0.1f;
        float RPMDamage = 0.1f;
        float MisshiftDamage = 5.0f;
    } MTParams;

    // [GAMEPLAY_ASSISTS]
    struct {
        bool SimpleBike = false;
        bool HillGravity = false;
        bool AutoGear1 = false;
        bool AutoLookBack = false;
        bool ThrottleStart = false;
        bool HidePlayerInFPV = false;
        bool DefaultNeutral = true;
    } GameAssists;

    // [DRIVING_ASSISTS]
    struct {
        struct {
            bool Enable = false;
            // true: only applied to abs-less vehicles
            bool Filter = true;
        } ABS;

        struct {
            // 0 Disabled, 1 Brake, 2 Throttle (patch) 
            int Mode = 0;
            // tyre speed threshold, m/s
            float SlipMax = 2.5f;
        } TCS;

        struct {
            bool Enable = false;

            float OverMin = 05.0f; // deg
            float OverMax = 15.0f; // deg

            float OverMinComp = 0.0f; // brake mult
            float OverMaxComp = 2.0f; // brake mult

            float UnderMin = 5.0f; // deg
            float UnderMax = 10.0f; // deg

            float UnderMinComp = 0.0f; // brake mult
            float UnderMaxComp = 1.0f; // brake mult

        } ESP;
    } DriveAssists;

    // [SHIFT_OPTIONS]
    struct {
        bool UpshiftCut = true;
        bool DownshiftBlip = true;
        float ClutchRateMult = 1.0f;
        float RPMTolerance = 0.2f;
    } ShiftOptions;

    // [AUTO_PARAMS]
    struct {
        // Lower = upshift later
        float UpshiftLoad = 0.05f;
        // Higher = downshift later
        float DownshiftLoad = 0.60f;
        // Don't upshift until next gears' RPM is over this value.
        float NextGearMinRPM = 0.33f;
        // Downshift when RPM drops below this value.
        float CurrGearMinRPM = 0.27f;
        // Lower = keep in low gear longer // eco - 0.33
        float EcoRate = 0.05f;
        // Timeout mult for not downshifting after an upshift
        float DownshiftTimeoutMult = 1.0f;
    } AutoParams;

    // [CUSTOM_STEERING]
    struct {
        // 0 Default, 1 Enhanced
        int Mode = 0;
        float CountersteerMult = 1.0f;
        // In Degrees
        float CountersteerLimit = 15.0f;
        float SteeringMult = 1.0f;
        float SteeringReduction = 1.0f;
        float Gamma = 1.0f;
        bool CustomRotation = false;
        float CustomRotationDegrees = 900.0f;
    } CustomSteering;

    // [HUD]
    struct {
        bool Enable = true;
        bool Always = true;
        // Fonts:
        // 0 - Chalet London
        // 1 - Sign Painter
        // 2 - Slab Serif
        // 4 - Chalet Cologne
        // 7 - Pricedown
        int Font = 4;

        // Levels:
        // 0 - Debug
        // 1 - Info
        // 2 - Error/UI (LogLevel WARN)
        // 3 - None
        int NotifyLevel = INFO;

        struct {
            bool Enable = true;
            float XPos = 0.9525f;
            float YPos = 0.885f;
            float Size = 0.700f;
            int TopColorR = 255;
            int TopColorG = 63;
            int TopColorB = 63;
        } Gear;

        struct {
            bool Enable = true;
            float XPos = 0.935f;
            float YPos = 0.885f;
            float Size = 0.700f;
        } ShiftMode;

        struct {
            // can be kph, mph, or ms
            std::string Speedo = "kph";
            bool ShowUnit = true;
            float XPos = 0.860f;
            float YPos = 0.885f;
            float Size = 0.700f;
        } Speedo;

        struct {
            bool Enable = true;
            float Redline = 0.850f;

            float XPos = 0.120f;
            float YPos = 0.765f;
            float XSz = 0.140f;
            float YSz = 0.005f;

            int BgR = 0;
            int BgG = 0;
            int BgB = 0;
            int BgA = 128;

            int FgR = 255;
            int FgG = 255;
            int FgB = 255;
            int FgA = 255;

            int RedlineR = 255;
            int RedlineG = 92;
            int RedlineB = 0;
            int RedlineA = 255;

            int RevLimitR = 255;
            int RevLimitG = 0;
            int RevLimitB = 0;
            int RevLimitA = 255;
        } RPMBar;

        struct {
            bool Enable = true;
            bool Always = false;
            float ImgXPos = 0.22f;
            float ImgYPos = 0.80f;
            float ImgSize = 0.05f;

            float PedalXPos = 0.22f;
            float PedalYPos = 0.90f;
            float PedalXSz = 0.04f;
            float PedalYSz = 0.10f;
            float PedalXPad = 0.0f;
            float PedalYPad = 0.0f;
            int PedalBgA = 92;

            int PedalThrottleR = 0;
            int PedalThrottleG = 255;
            int PedalThrottleB = 0;
            int PedalThrottleA = 255;

            int PedalBrakeR = 255;
            int PedalBrakeG = 0;
            int PedalBrakeB = 0;
            int PedalBrakeA = 255;

            int PedalClutchR = 0;
            int PedalClutchG = 0;
            int PedalClutchB = 255;
            int PedalClutchA = 255;
        } Wheel;

        struct {
            bool Enable = false;
            float XPos = 0.500f;
            float YPos = 0.035f;
            float Size = 1.000f;
        } DashIndicators;
    } HUD;

    // [CONTROLLER]
    struct {
        int HoldTimeMs = 250;
        int MaxTapTimeMs = 200;
        float TriggerValue = 0.75f;

        bool ToggleEngine = false;

        bool BlockCarControls = false;
        bool IgnoreShiftsUI = false;
        bool BlockHShift = true;

        //long ShiftUpBlocks = -1;
        //long ShiftDownBlocks = -1;
        //long ClutchBlocks = -1;

        struct {
            bool Enable = false;
            //long ShiftUpBlocks = -1;
            //long ShiftDownBlocks = -1;
            //long ClutchBlocks = -1;
        } Native;
    } Controller;

    // [MISC]
    struct {
        bool UDPTelemetry = true;
        bool DashExtensions = true;
    } Misc;

    // [UPDATE]
    struct {
        bool EnableUpdate = true;
        std::string IgnoredVersion = "v0.0.0";
    } Update;

    // [DEBUG]
    struct {
        int LogLevel = INFO;
        bool DisplayInfo = false;
        bool DisplayGearingInfo = false;
        bool DisplayWheelInfo = false;
        bool DisplayFFBInfo = false;
        bool DisplayNPCInfo = false;
        bool DisableInputDetect = false;
        bool DisablePlayerHide = false;

        struct {
            bool EnableTimers = false;
            std::vector<TimerParams> Timers{
                { "kph", 0.0f, 100.0f, 0.1f },
                { "mph", 0.0f,  60.0f, 0.1f }
            };
            struct {
                bool Enable = false;
                float PosX = 0.075f;
                float PosY = 0.125f;
                float Size = 0.200f;
            } GForce;
        } Metrics;

        bool DisableNPCBrake = false;
        bool DisableNPCGearbox = false;
    } Debug;

    // settings_wheel.ini parts
    struct {
        // [OPTIONS]
        struct {
            bool Enable = true;
            bool SyncRotation = true;
            bool LogiLEDs = false;
            bool HPatternKeyboard = false;
            bool UseShifterForAuto = false;
        } Options;

        // [INPUT_DEVICES]
        struct {
            std::vector<GUID> RegisteredGUIDs;
        } InputDevices;

        // [FORCE_FEEDBACK]
        struct {
            bool Enable = true;
            bool Scale = true;
            int AntiDeadForce = 0;
            float SATAmpMult = 1.0f;
            int SATMax = 10000;
            float SATFactor = 0.66f;
            int DamperMax = 50;
            int DamperMin = 10;
            float DamperMinSpeed = 1.2f; // TargetSpeed in m/s
            float DetailMult = 2.5f;
            int DetailLim = 20000;
            int DetailMAW = 1;
            float CollisionMult = 1.0f;
            float Gamma = 0.8f;
            float MaxSpeed = 80.0f;
        } FFB;

        // [STEER]
        struct {
            float AngleMax = 900.0f;
            float AngleCar = 720.0f;
            float AngleBike = 180.0f;
            float AngleBoat = 360.0f;
            float SteerMult = 1.0f;
            float Gamma = 1.0f;
            float AntiDeadZone = 0.25f;
            float DeadZone = 0.0f;
            float DeadZoneOffset = 0.0f;
            int Min = -1;
            int Max = -1;
        } Steering;

        // [THROTTLE]
        struct {
            float Gamma = 1.0f;
            float AntiDeadZone = 0.25f;
            int Min = -1;
            int Max = -1;
        } Throttle;

        // [BRAKE]
        struct {
            float Gamma = 1.0f;
            float AntiDeadZone = 0.25f;
            int Min = -1;
            int Max = -1;
        } Brake;

        // [CLUTCH]
        struct {
            int Min = -1;
            int Max = -1;
        } Clutch;

        // [HANDBRAKE_ANALOG]
        struct {
            int Min = -1;
            int Max = -1;
        } HandbrakeA;
    } Wheel;

    // Methods
    /*
     *  Checks if GUID already exists and returns device index
     *  otherwise appends GUID and returns new device index
     */
    ptrdiff_t SteeringAppendDevice(const GUID & dev_guid, const std::string& dev_name);
    int GUIDToDeviceIndex(GUID guid);

    void SteeringSaveAxis(const std::string &confTag, ptrdiff_t index, const std::string &axis, int minVal, int maxVal);
    void SteeringSaveFFBAxis(const std::string &confTag, ptrdiff_t index, const std::string &axis);
    void SteeringSaveButton(const std::string &confTag, ptrdiff_t index, int button);
    void SteeringSaveHShifter(const std::string &confTag, ptrdiff_t index, const std::vector<int>& button);
    void KeyboardSaveKey(const std::string &confTag, const std::string &key);
    void ControllerSaveButton(const std::string &confTag, const std::string &button);
    void LControllerSaveButton(const std::string & confTag, int button);
    void SteeringAddWheelToKey(const std::string & conftag, ptrdiff_t index, int button, const std::string & keyName);
    bool SteeringClearWheelToKey(int button);

private:
    void parseSettingsGeneral();
    void parseSettingsControls(CarControls* scriptControl);
    void parseSettingsWheel(CarControls *scriptControl);

    // Just looks up which GUID corresponds with what number and returns the GUID.
    GUID DeviceIndexToGUID(int device, std::vector<GUID> guids);

    int nDevices = 0;
    std::string settingsGeneralFile;
    std::string settingsControlsFile;
    std::string settingsWheelFile;
    std::string settingsMenuFile;
};
