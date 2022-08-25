modded class MissionGameplay
{
  protected bool RecivedEvents;
  override void OnUpdate(float timeslice)
  {
        super.OnUpdate(timeslice);
        KR_KingOfTheHillClientManager.GetInstance().OnUpdate(timeslice);

        PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
        if(player && !RecivedEvents){
          GetGame().RPCSingleParam(player, KOTH_RPCs.RPC_GETALLEVENTS, null, true);
          RecivedEvents = true;
        }
    }

    override void OnMissionFinish()
	  {
      super.OnMissionFinish();
      RecivedEvents = false;
      KR_KingOfTheHillClientManager.GetInstance().m_ZoneMenu.HandleShow(false);
    }

    override void OnKeyRelease(int key)
    {
          if(key == KeyCode.KC_ESCAPE)
          {
              KR_KingOfTheHillClientManager().GetInstance().CloseAdminMenu();
          }
          super.OnKeyRelease(key);

        if (GetUApi() && !m_UIManager.IsMenuOpen(MENU_CHAT_INPUT) && key == KeyCode.KC_NUMPAD5)
        {
            KR_KingOfTheHillClientManager().GetInstance().HandleAdminMenu();
        }
    }
};