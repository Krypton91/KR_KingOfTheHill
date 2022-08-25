modded class MissionBase 
{
    override UIScriptedMenu CreateScriptedMenu (int id) 
    {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) 
        {
            switch (id) 
            {
                case KR_KOTH_ADMINMENUID:
                    menu = new KR_KOTH_ADMIN_UI;
                    break;
            }
            if (menu)
            {
                menu.SetID(id);
            }
        }
        return menu;
    }
};