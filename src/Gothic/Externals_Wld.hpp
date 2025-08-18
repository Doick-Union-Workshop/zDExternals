namespace GOTHIC_NAMESPACE
{
    static zSTRING Wld_GetPlayerPortalRoom()
    {
        if (zSTRING* name = ogame->GetPortalRoomManager()->curPlayerPortal)
            return *name;
        return zSTRING{};
    }

    static int Wld_IsDay()
    {
        return ogame->GetWorldTimer()->IsDay(); // 6,30-18,30
    }

    static int Wld_IsNight()
    {
		return ogame->GetWorldTimer()->IsNight(); // 18,30-6,30
    }

    static zSTRING Wld_GetWorldName()
    {
	    return ogame->GetGameWorld()->GetWorldName();
    }

    static float GetTimeAsFraction(const int t_hour, const int t_minutes)
    {
        int totalMinutesInDay = 24 * 60;
        int totalMinutes = t_hour * 60 + t_minutes;
        return static_cast<float>(totalMinutes) / static_cast<float>(totalMinutesInDay);
    }

    static int Wld_SetRainTime(const int t_startHr, const int t_startMin, const int t_endHr, const int t_endMin)
    {
        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Wld_SetRainTime");
        zCSkyControler_Outdoor* skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(ogame->GetGameWorld()->GetActiveSkyControler());

        if (!skyCtrl)
        {
            log->Warning("zCSkyControler_Outdoor not found");
            return 0;
        }

        if (ogame->GetWorldTimer()->IsTimeBetween(t_startHr, t_startMin, t_endHr, t_endMin))
        {
            int startHr = (t_startHr + 12) % 24;
            int endHr = (t_endHr + 12) % 24;

            if (startHr > endHr)
            {
                log->Info("Rain at 12 noon is not possible!");
                return 0;
            }

            float startF = GetTimeAsFraction(startHr, t_startMin);
            float endF = GetTimeAsFraction(endHr, t_endMin);

            skyCtrl->rainFX.timeStartRain = startF;
            skyCtrl->rainFX.timeStopRain = endF;

            return 1;
        }

        return 0;
    }

    static void Wld_SetRainOn()
    {
        zCSkyControler_Outdoor* skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(ogame->GetGameWorld()->GetActiveSkyControler());

        if (!skyCtrl) return;

        skyCtrl->rainFX.timeStartRain = 0;
        skyCtrl->rainFX.timeStopRain = 1.0f;
    }

    static void Wld_SetRainOff()
    {
        zCSkyControler_Outdoor* skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(ogame->GetGameWorld()->GetActiveSkyControler());

        if (!skyCtrl) return;

        skyCtrl->rainFX.timeStartRain = 0;
        skyCtrl->rainFX.timeStopRain = 0;
        skyCtrl->rainFX.soundVolume = 0;

        if (!skyCtrl->rainFX.outdoorRainFX) return;

		skyCtrl->rainFX.outdoorRainFX->UpdateSound(0);
    }

    static zVEC3 GetColorFromString(const zSTRING& s)
    {
        return zVEC3((s.PickWord_Old(1, "\r\t ").ToFloat()),
            (s.PickWord_Old(2, "\r\t ").ToFloat()),
            (s.PickWord_Old(3, "\r\t ").ToFloat()));
    }

    static void Wld_OverrideWorldFogColors(const int t_index, const zSTRING& t_color)
    {
        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Wld_OverrideWorldFogColors");
        zCSkyControler_Outdoor* skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(ogame->GetGameWorld()->GetActiveSkyControler());

        if (!skyCtrl)
        {
            log->Warning("zCSkyControler_Outdoor not found");
            return;
        }

        zVEC3 color = GetColorFromString(t_color);
        skyCtrl->fogColorDayVariations.Insert(color);
    }
}
