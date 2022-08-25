class KR_KOTH_ADMIN_UI extends UIScriptedMenu
{
    protected bool                                  m_IsMenuInitialized;
    protected bool                                  m_IsTabAnimationRunning;
    protected ButtonWidget                          m_CloseBtn;

    /* Sidebar */
    protected ButtonWidget                          m_TabEventsBtn;
    protected ButtonWidget                          m_TabZonesBtn;
    protected ButtonWidget                          m_RewardsBtn;
    protected ButtonWidget                          m_MiscsBtn;

    /* Tabs */
    protected Widget                                m_ActiveTab;
    protected Widget                                m_EventsTab;
    protected Widget                                m_ZonesTab;

    //Popup
    protected Widget                                m_ManageEventPopup;
    protected EditBoxWidget                         m_ManageEventPosX;
    protected EditBoxWidget                         m_ManageEventPosY;
    protected EditBoxWidget                         m_ManageEventPosZ;
    protected EditBoxWidget                         m_ManageEventCPRad;
    protected EditBoxWidget                         m_ManageEventEventRad;
    protected EditBoxWidget                         m_ManageEventEventAiAmount;
    protected EditBoxWidget                         m_ManageEventEventZoneName;
    protected EditBoxWidget                         m_ManageEventEventLootTier;
    protected EditBoxWidget                         m_ManageEventEventLootObjectList;
    protected ButtonWidget                          m_StartForceEventBtn;

    protected MapWidget                             m_Map;

    autoptr KR_KingOfTheHillLocation                m_ForeceLocation;

    override Widget Init()
    {
        if(!m_IsMenuInitialized)
        {
            layoutRoot                          = GetGame().GetWorkspace().CreateWidgets(GetLayoutPath());
            m_CloseBtn                          = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseBtn"));
            m_TabEventsBtn                      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnEventManager"));
            m_TabZonesBtn                       = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnConfigManager"));
            m_RewardsBtn                        = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnRewardsManager"));
            m_MiscsBtn                          = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnMiscsManager"));
            m_StartForceEventBtn                = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnForceStartEvent"));
            m_Map                               = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
            m_EventsTab                         = Widget.Cast(layoutRoot.FindAnyWidget("EventsTab"));
            m_ZonesTab                          = Widget.Cast(layoutRoot.FindAnyWidget("Zones"));
            m_ManageEventPopup                  = Widget.Cast(layoutRoot.FindAnyWidget("PanelHandleEvent"));

            m_ManageEventPosX                   = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("XPosBox"));
            m_ManageEventPosY                   = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("YPosBox"));
            m_ManageEventPosZ                   = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZPosBox"));
            m_ManageEventCPRad                  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZPosBox0"));
            m_ManageEventEventRad               = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZPosBox1"));
            m_ManageEventEventAiAmount          = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AiAmountBox"));
            m_ManageEventEventZoneName          = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AiAmountBox0"));
            m_ManageEventEventLootTier          = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AiAmountBox1"));
            m_ManageEventEventLootObjectList    = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AiAmountBox2"));

            m_IsMenuInitialized = true;
            m_ActiveTab = m_EventsTab;
        }

        return layoutRoot;
    }

    override bool OnClick( Widget w, int x, int y, int button )	
    {
        switch(w)
        {
            case m_CloseBtn:
            {
                GetGame().GetUIManager().Back();
                break;
            }
            case m_TabEventsBtn:
            {
                SwitchTabWithAnimation(m_EventsTab);
                break;
            }
            case m_TabZonesBtn:
            {
                SwitchTabWithAnimation(m_ZonesTab);
                break;
            }
            case m_StartForceEventBtn:
            {
                ForceAdminHill();
            }
        }

        return super.OnClick(w, x, y, button);
    }

    bool OnDoubleClick(Widget w, int x, int y, int button)
	{
        if(w == m_Map)
        {
            HandleMapDoubleClick(x, y);
            return true;
        }

        return super.OnClick(w, x, y, button);
    }

    void HandleMapDoubleClick(float x, float y)
    {
        if(m_Map)
        {
            vector pos = m_Map.ScreenToMap(Vector(x, y, 0));
            m_Map.ClearUserMarks();
            m_Map.AddUserMark(pos, "FORCE HILL POSTION", ARGB(255, 255, 0, 0), "KR_KingOfTheHill/GUI/images/FlagIcon.edds");
            OpenPanelHandleEvent(pos);
        }
    }

    void ForceAdminHill()
    {
        string ZoneName = m_ManageEventEventZoneName.GetText();
        float Radius = m_ManageEventEventRad.GetText().ToFloat();
        float CaptureRadius = m_ManageEventCPRad.GetText().ToFloat();
        bool ResetCaptureTimeAfterAllPlayersLeavedZone = false;
        vector Position = Vector(m_ManageEventPosX.GetText().ToFloat(), m_ManageEventPosY.GetText().ToFloat(), m_ManageEventPosZ.GetText().ToFloat());
        int AISpawnCount = m_ManageEventEventAiAmount.GetText().ToInt();
        int LootTier    = m_ManageEventEventAiAmount.GetText().ToInt();
        string ObjectListName = m_ManageEventEventLootObjectList.GetText();

        m_ForeceLocation = new KR_KingOfTheHillLocation(ZoneName, Radius, CaptureRadius, ResetCaptureTimeAfterAllPlayersLeavedZone, Position, AISpawnCount, LootTier, ObjectListName);

        //Send RPC to server.

    }

    void OpenPanelHandleEvent(vector initPos)
    {
        float X, Y, Z;
        X = initPos[0]
        Y = initPos[1]
        Z = initPos[2]

        m_ManageEventPosX.SetText(X.ToString());
        m_ManageEventPosY.SetText(Y.ToString());
        m_ManageEventPosZ.SetText(Z.ToString());
        m_ManageEventCPRad.SetText("20");
        m_ManageEventEventRad.SetText("150");
        m_ManageEventEventAiAmount.SetText("10");
        m_ManageEventEventZoneName.SetText("Admin Force Zone");
        m_ManageEventEventLootTier.SetText("1");
        m_ManageEventEventLootObjectList.SetText("none");
        m_ManageEventPopup.Show(true);
    }

    enum TabControllerTab
    {
        EVENTS = 0,
        ZONES, 
        REWARDS,
        MISCS
    }

    int currentTransitionProgress;
	float centerX, leftX;
	const int TRANSITION_ANIMATION_STEPS = 25;
	const float TAB_OFFSET = 0.1;
    
    void SwitchTabWithAnimation(Widget tab)
    {
        if(!tab)
            return;
        
        if(!m_IsTabAnimationRunning)
        {
            float width, height, x, y;
            tab.Show(true);
            if(m_ActiveTab)
            {
                m_IsTabAnimationRunning = true;
                m_ActiveTab.GetSize(width, height);
                m_ActiveTab.GetPos(x, y);

                float XOffset = (x - width) - TAB_OFFSET;
                float TransSize = XOffset / TRANSITION_ANIMATION_STEPS;

                currentTransitionProgress = 0;

                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(MoveTabs, 10, true, m_ActiveTab, tab, TransSize);
                m_ActiveTab = tab;
                m_ActiveTab.Show(true);
            }
        }
    }

    void MoveTabs(Widget oldTab, Widget newTab, float size)
    {
        currentTransitionProgress++;
        float x, y;
        oldTab.GetPos(x, y);
		oldTab.SetPos((x - size), y, true);
		newTab.GetPos(x, y);
		newTab.SetPos((x - size), y, true);

        if (currentTransitionProgress >= TRANSITION_ANIMATION_STEPS)		
        {
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(MoveTabs);
			newTab.SetPos(centerX, y, true);
            oldTab.Show(false);
			m_IsTabAnimationRunning = false;
		}
    }

    string GetLayoutPath()
    {
        return "KR_KingOfTheHill/GUI/layouts/KOTH_AdminMenu.layout";
    }


    override void OnShow()
	{
		super.OnShow();
		PPEffects.SetBlurMenu(0.5);
		GetGame().GetInput().ChangeGameFocus(1);
		SetFocus( layoutRoot );
		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
	}

    override void OnHide()
	{
		super.OnHide();
		PPEffects.SetBlurMenu(0);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().PlayerControlEnable( false );
        GetGame().GetUIManager().ShowUICursor( false );
		Close();
    }
};