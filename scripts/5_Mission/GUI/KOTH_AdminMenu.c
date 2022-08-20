class KR_KOTH_ADMIN_UI extends UIScriptedMenu
{
    protected bool                                  m_IsMenuInitialized;
    protected bool                                  m_IsTabAnimationRunning;
    protected ButtonWidget                          m_CloseBtn;
    protected Widget                                m_ActiveTab;
    override Widget Init()
    {
        if(!m_IsMenuInitialized)
        {
            layoutRoot                      = GetGame().GetWorkspace().CreateWidgets(GetLayoutPath());

            m_IsMenuInitialized = true;
        }
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
	bool Transitioning = false;
	const int TRANSITION_ANIMATION_STEPS = 40;
	const float TAB_OFFSET = 0.05;
    
    void SwitchTabWithAnimation(Widget tab)
    {
        if(!tab)
            return;
        
        if(!m_IsTabAnimationRunning)
        {
            float width, height, x, y;

            if(m_ActiveTab)
            {
                m_ActiveTab.GetSize(width, height);
                m_ActiveTab.GetPosition(x, y);

                float XOffset = (x - width) - TAB_OFFSET;
                float TransSize = XOffset / TRANSITION_ANIMATION_STEPS;

                currentTransitionProgress = 0;

                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(MoveTabs, 10, true, m_ActiveTab, tab, TransSize);
                m_ActiveTab = tab;
            }
        }
    }

    void MoveTabs(Widget oldTab, Widget newTab, float size)
    {
        currentTransitionProgress++;
        float x, y;
        oldTab.GetPos(x, y);
		oldTab.SetPos((x - stepSize), y, true);
		newTab.GetPos(x, y);
		newTab.SetPos((x - stepSize), y, true);

        if (currentTransitionProgress >= TRANSITION_ANIMATION_STEPS)		
        {
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(MoveTabs);
			newTab.SetPos(centerX, y, true);
			oldTab.SetPos(leftX, y, true);
			m_IsTabAnimationRunning = false;
		}
    }

    string GetLayoutPath()
    {
        return "KR_KingOfTheHill/GUI/layouts/KOTH_AdminMenu.layout";
    }
};