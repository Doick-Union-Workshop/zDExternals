namespace GOTHIC_NAMESPACE
{
    static void Mob_SetFocusName(const zSTRING& t_mobName, const zSTRING& t_focusName)
    {
        if (t_mobName.IsEmpty()) return;

        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Mob_SetFocusName");

        zSTRING mobName = t_mobName;
        mobName.Upper();
        zCVob* vob = ogame->GetGameWorld()->SearchVobByName(mobName);

        if (!vob)
        {
            log->Error("No Vob found with specified Vobname: {0}", mobName.ToChar());
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

        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Mob_GetFocusName");

        zSTRING mobName = t_mobName;
        mobName.Upper();
        zCVob* vob = ogame->GetGameWorld()->SearchVobByName(mobName);

        if (!vob)
        {
            log->Error("No Vob found with specified Vobname: {0}", mobName.ToChar());
            return zSTRING{};
        }

        oCMOB* mob = vob->CastTo<oCMOB>();
        return mob->GetName();
    }
}