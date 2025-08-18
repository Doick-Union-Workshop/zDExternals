namespace GOTHIC_NAMESPACE
{
    static void Menu_SetItemText(const zSTRING& t_name, const zSTRING& t_text)
    {
        if (t_name.IsEmpty()) return;

        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Menu_SetItemText");

        zSTRING name = t_name;
        name.Upper();
        zCMenuItem* menuItem = zCMenuItem::GetByName(name);

        if (!menuItem)
        {
            log->Warning("Invalid Menu Item: {0}", name.ToChar());
            return;
        }

        menuItem->SetText(t_text, 0, 0);
#if ENGINE > Engine_G1A
        menuItem->Release();
#else
        delete menuItem;
#endif
    }

    static zSTRING Menu_GetItemText(const zSTRING& t_name)
    {
        if (t_name.IsEmpty())
            return zSTRING{};

        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Menu_GetItemText");

        zSTRING name = t_name;
        name.Upper();
        zCMenuItem* menuItem = zCMenuItem::GetByName(name);

        if (!menuItem)
        {
            log->Warning("Invalid Menu Item: {0}", name.ToChar());
            return zSTRING{};
        }

        zSTRING result = menuItem->GetText(0);
#if ENGINE > Engine_G1A
        menuItem->Release();
#else
        delete menuItem;
#endif
        return result;
    }

    // For menu parser
    static int Menu_SetItemText_Old()
    {
        auto const par = zCParser::GetParser();
        zSTRING menuItemName, menuItemText;
        par->GetParameter(menuItemText);
        par->GetParameter(menuItemName);
        menuItemName = menuItemName.Upper();
        zCMenuItem* menuItem = zCMenuItem::GetByName(menuItemName);

        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Menu_SetItemText_Old");

        if (!menuItem)
        {
            log->Warning("Invalid Menu Item: {0}", menuItemName.ToChar());
            return 0;
        }

        menuItem->SetText(menuItemText, 0, 0);
#if ENGINE == Engine_G2A
        menuItem->Release();
#else
        menuItem = NULL;
#endif
        return 0;
    }

    static int Menu_GetItemText_Old()
    {
        static zSTRING result = "";
        auto const par = zCParser::GetParser();
        zSTRING menuItemName;
        par->GetParameter(menuItemName);
        menuItemName = menuItemName.Upper();
        zCMenuItem* menuItem = zCMenuItem::GetByName(menuItemName);

        static Utils::Logger* log = Utils::CreateLogger("zDExternals::Menu_GetItemText_Old");

        if (!menuItem)
        {
            log->Warning("Invalid Menu Item: {0}", menuItemName.ToChar());
            par->SetReturn((zSTRING&)result);
            return 0;
        }

        result = (zSTRING&)menuItem->GetText(0);
#if ENGINE == Engine_G2A
        menuItem->Release();
#else
        menuItem = NULL;
#endif
        par->SetReturn(result);
        return 0;
    }
}