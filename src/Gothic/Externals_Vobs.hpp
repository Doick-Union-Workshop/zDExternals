namespace GOTHIC_NAMESPACE
{
#pragma push_macro("Z")
#undef Z

    struct C_POSITION {
        int X;
        int Y;
        int Z;
    };

    static void SetPositionWorld(zCVob* t_vob, const zVEC3& t_position)
    {
        if (!t_vob || t_position == zVEC3{})
            return;

        const bool collDetectionStatic = t_vob->collDetectionStatic;
        const bool collDetectionDynamic = t_vob->collDetectionDynamic;
        t_vob->collDetectionStatic = 0;
        t_vob->collDetectionDynamic = 0;
        t_vob->SetPositionWorld(t_position);
        t_vob->collDetectionStatic = collDetectionStatic;
        t_vob->collDetectionDynamic = collDetectionDynamic;
    }

    template<typename T>
    static void Wld_InsertVob(const zSTRING& t_vobName, const zSTRING& t_pointName)
    {
        if (t_vobName.IsEmpty() || t_pointName.IsEmpty())
            return;

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Wld_InsertVob");

        zSTRING vobName = t_vobName;
        zSTRING pointName = t_pointName;
        pointName.Upper();
        T* vob = new T{};
        oCWorld* world = ogame->GetGameWorld();
        zCWaypoint* wp = world->wayNet->GetWaypoint(pointName);
        zVEC3 pos;

        if (wp) {
            pos = wp->GetPositionWorld();
        }
        else
        {
            zCVob* pointVob = world->SearchVobByName(pointName);

            if (!pointVob)
            {
                log->Warning("No Vob found with specified Vobname: {0}", pointName.ToChar());
                vob->Release();
                return;
            }

            pos = pointVob->GetPositionWorld();
        }

        vob->SetVobName(vobName.Upper());
        world->AddVob(vob);
        SetPositionWorld(vob, pos);
        vob->Release();
    }

    template<typename T>
    static void Wld_InsertVobPos(const zSTRING& t_vobName, C_POSITION* t_vobPosition)
    {
        if (t_vobName.IsEmpty() || !t_vobPosition)
            return;
        
        zSTRING vobName = t_vobName;
        T* vob = new T{};
        zVEC3 pos = zVEC3(
            (float)t_vobPosition->X,
            (float)t_vobPosition->Y,
            (float)t_vobPosition->Z
        );
        vob->SetVobName(vobName.Upper());
        ogame->GetGameWorld()->AddVob(vob);
        SetPositionWorld(vob, pos);
        vob->Release();
    }

    static int Wld_RemoveVob(const zSTRING& t_vobName)
    {
        if (t_vobName.IsEmpty()) return 0;

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Wld_RemoveVob");

        oCWorld* world = ogame->GetGameWorld();
        zSTRING vobName = t_vobName;
        vobName.Upper();
        zCVob* vob = world->SearchVobByName(vobName);

        if (!vob)
        {
            log->Warning("No Vob found with specified Vobname: {0}", vobName.ToChar());
            return 0;
        }

        world->RemoveVob(vob);
        vob->Release();
        return 1;
    }

    static void Vob_MoveTo(const zSTRING& t_vobName, const zSTRING& t_pointName)
    {
        if (t_vobName.IsEmpty() || t_pointName.IsEmpty())
            return;

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Vob_MoveTo");

        oCWorld* world = ogame->GetGameWorld();
        zSTRING vobName = t_vobName;
        vobName.Upper();
        zCVob* vob = world->SearchVobByName(vobName);

        if (!vob)
        {
            log->Warning("No Vob found with specified Vobname: {0}", vobName.ToChar());
            return;
        }

        zSTRING pointName = t_pointName;
        pointName.Upper();
        zCWaypoint* wp = world->wayNet->GetWaypoint(pointName);
        zVEC3 pos;

        if (wp) {
            pos = wp->GetPositionWorld();
        }
        else
        {
            zCVob* pointVob = world->SearchVobByName(pointName);
            if (!pointVob) return;
            pos = pointVob->GetPositionWorld();
        }

        SetPositionWorld(vob, pos);
    }

    static C_POSITION* Wld_GetPos(const int t_posX, const int t_posY, const int t_posZ)
    {
        C_POSITION* vobPosition = new C_POSITION;
        vobPosition->X = t_posX;
        vobPosition->Y = t_posY;
        vobPosition->Z = t_posZ;
        return vobPosition;
    }

    static void Vob_Rotate(const zSTRING& t_vobName, C_POSITION* t_vobPosition)
    {
        if (t_vobName.IsEmpty() || !t_vobPosition)
            return;

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Vob_MoveTo");

        zSTRING vobName = t_vobName;
        vobName.Upper();
        zCVob* vob = ogame->GetGameWorld()->SearchVobByName(vobName);

        if (!vob)
        {
            log->Warning("No Vob found with specified Vobname: {0}", vobName.ToChar());
            return;
        }

        const bool collDetectionStatic = vob->collDetectionStatic;
        const bool collDetectionDynamic = vob->collDetectionDynamic;
        vob->collDetectionStatic = 0;
        vob->collDetectionDynamic = 0;
        vob->RotateWorldX((float)t_vobPosition->X);
        vob->RotateWorldY((float)t_vobPosition->Y);
        vob->RotateWorldZ((float)t_vobPosition->Z);
        vob->collDetectionStatic = collDetectionStatic;
        vob->collDetectionDynamic = collDetectionDynamic;
    }

    static void Vob_SetVisual(const zSTRING& t_vobName, const zSTRING& t_visualName)
    {
        if (t_vobName.IsEmpty()) return;

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Vob_SetVisual");

        zSTRING vobName = t_vobName;
        vobName.Upper();
        zCVob* vob = ogame->GetGameWorld()->SearchVobByName(vobName);

        if (!vob)
        {
            log->Warning("No Vob found with specified Vobname: {0}", vobName.ToChar());
            return;
        }

        zSTRING visualName = t_visualName;
        vob->SetVisual(zCVisual::LoadVisual(visualName.Upper()));
    }

    static void Vob_SetOnFloor(const zSTRING& t_vobName)
    {
        if (t_vobName.IsEmpty()) return;

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Vob_SetOnFloor");

        zSTRING vobName = t_vobName;
        vobName.Upper();
        zCVob* vob = ogame->GetGameWorld()->SearchVobByName(vobName);

        if (!vob)
        {
            log->Warning("No Vob found with specified Vobname: {0}", vobName.ToChar());
            return;
        }

        oCVob* obj = dynamic_cast<oCVob*>(vob);

        if (!obj)
        {
            log->Warning("Vob found, but it is not an oCVob: {0}", vobName.ToChar());
            return;
        }

        zVEC3 pos = vob->GetPositionWorld();
        obj->SetOnFloor(pos);
    }

    static void Mob_SetFocusName(const zSTRING& t_mobName, const zSTRING& t_focusName)
    {
        if (t_mobName.IsEmpty()) return;

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Mob_SetFocusName");

        zSTRING mobName = t_mobName;
        mobName.Upper();
        zCVob* vob = ogame->GetGameWorld()->SearchVobByName(mobName);

        if (!vob)
        {
            log->Warning("No Vob found with specified Vobname: {0}", mobName.ToChar());
            return;
        }

        oCMOB* mob = vob->CastTo<oCMOB>();
        zSTRING focusName = t_focusName;
        mob->SetName(focusName.Upper());
    }

    static zSTRING Mob_GetFocusName(const zSTRING& t_mobName)
    {
        if (t_mobName.IsEmpty())
            return zSTRING{};

        static Utils::Logger* log = Utils::CreateLogger("DSP::Externals::Mob_GetFocusName");

        zSTRING mobName = t_mobName;
        mobName.Upper();
        zCVob* vob = ogame->GetGameWorld()->SearchVobByName(mobName);

        if (!vob)
        {
            log->Warning("No Vob found with specified Vobname: {0}", mobName.ToChar());
            return zSTRING{};
        }

        oCMOB* mob = vob->CastTo<oCMOB>();
        return mob->GetName();
    }

#pragma pop_macro("Z")
}