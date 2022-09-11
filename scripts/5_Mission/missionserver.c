modded class MissionServer
{
    override void OnInit()
	{
        super.OnInit();
        float StartDelay = KR_KingOfTheHillConfig.Load().GetServerStartDelay();
        KOTHLoggingService.Log("Event Manager starts in " + StartDelay + " ms.");
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.InitKingOfTheHill, StartDelay, false);
    }

    void InitKingOfTheHill()
    {
        KingOfTheHillEventManager.GetInstance().Init();
    }

    override void OnUpdate(float timeslice)
	{
        KingOfTheHillEventManager.GetInstance().OnUpdate(timeslice);
		super.OnUpdate( timeslice );
	}
};