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

    protected MapWidget                             m_Map;
    protected autoptr KR_KOTH_POPUPEditor           m_PopupWindow;

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
            m_Map                               = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
            m_EventsTab                         = Widget.Cast(layoutRoot.FindAnyWidget("EventsTab"));
            m_ZonesTab                          = Widget.Cast(layoutRoot.FindAnyWidget("Zones"));

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
            m_PopupWindow = new KR_KOTH_POPUPEditor(m_Map);
            if(m_PopupWindow){
                m_PopupWindow.OpenEditor(x, y);
            }
        }
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