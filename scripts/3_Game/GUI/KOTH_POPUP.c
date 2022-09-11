class KR_KOTH_POPUPEditor extends ScriptedWidgetEventHandler 
{
    protected Widget                                m_EditorRoot;
    protected Widget                                m_Editor;
    protected ButtonWidget                          m_CloseBtn;
    protected ButtonWidget                          m_StartForceEventBtn;
    protected EditBoxWidget                         m_ManageEventPosX;
    protected EditBoxWidget                         m_ManageEventPosY;
    protected EditBoxWidget                         m_ManageEventPosZ;
    protected EditBoxWidget                         m_ManageEventCPRad;
    protected EditBoxWidget                         m_ManageEventEventRad;
    protected EditBoxWidget                         m_ManageEventEventAiAmount;
    protected EditBoxWidget                         m_ManageEventEventZoneName;
    protected EditBoxWidget                         m_ManageEventEventLootTier;
    protected EditBoxWidget                         m_ManageEventEventLootObjectList;

    protected float						            m_ScreenX;
	protected float						            m_ScreenY;
    protected float						            m_WidgetX;
	protected float						            m_WidgetY;
	protected float						            m_WidgetWidth;
	protected float						            m_WidgetHeight;

    autoptr KR_KingOfTheHillLocation                m_ForeceLocation;

    void KR_KOTH_POPUPEditor(Widget parent)
    {
        m_EditorRoot				= GetGame().GetWorkspace().CreateWidgets(GetLayoutPath(), parent);
        m_Editor                    = Widget.Cast(m_EditorRoot.FindAnyWidget("PanelHandleEvent"));
        m_CloseBtn                  = ButtonWidget.Cast(m_EditorRoot.FindAnyWidget("CancelHandleEBtn"));
        m_StartForceEventBtn        = ButtonWidget.Cast(m_EditorRoot.FindAnyWidget("BtnForceStartEvent"));
        m_ManageEventPosX           = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("XPosBox"));
        m_ManageEventPosY           = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("YPosBox"));
        m_ManageEventPosZ           = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("ZPosBox"));
        m_ManageEventCPRad          = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("ZPosBox0"));
        m_ManageEventEventRad       = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("ZPosBox1"));
        m_ManageEventEventAiAmount  = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("AiAmountBox"));
        m_ManageEventEventZoneName  = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("AiAmountBox0"));
        m_ManageEventEventLootTier  = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("AiAmountBox1"));
        m_ManageEventEventLootObjectList = EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget("AiAmountBox2"));

        m_EditorRoot.SetHandler(this);
        m_EditorRoot.Show(false);
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

    void OpenEditor(float x, float y)
    {
        float ScreenWidth = 0;
		float ScreenHeight = 0;
		GetGame().GetWorkspace().GetScreenSize(ScreenWidth, ScreenHeight);

        m_ScreenX = ScreenWidth;
		m_ScreenY = ScreenHeight;
        m_EditorRoot.GetSize(m_WidgetWidth, m_WidgetHeight);
        m_EditorRoot.Show(true);
        m_WidgetX  = x;
		m_WidgetY  = y;
		float maxX = m_ScreenX - m_WidgetWidth - 3;
		float maxY = m_ScreenY - m_WidgetHeight;
		if (m_WidgetX > maxX)
        {
			m_WidgetX = m_WidgetX - m_WidgetWidth - 10;
		}
			
		if (m_WidgetY > maxY)
        {
			m_WidgetY = m_WidgetY - m_WidgetHeight - 24;
		}

        m_ManageEventPosX.SetText(x.ToString());
        m_ManageEventPosY.SetText(y.ToString());
        m_ManageEventPosZ.SetText(GetGame().SurfaceY(x, y).ToString());
        m_ManageEventCPRad.SetText("20");
        m_ManageEventEventRad.SetText("150");
        m_ManageEventEventAiAmount.SetText("10");
        m_ManageEventEventZoneName.SetText("Admin Force Zone");
        m_ManageEventEventLootTier.SetText("1");
        m_ManageEventEventLootObjectList.SetText("none");
        Print("Sucessfully Opened Event PopUp");
    }

    void CloseEditor()
    {
		m_EditorRoot.Show(false);
	}

    override bool OnClick( Widget w, int x, int y, int button )
	{
        if(w == m_CloseBtn)
        {
            m_EditorRoot.Show(false);
        }

        return super.OnClick(w, x, y, button);
    }


    string GetLayoutPath()
    {
        return "KR_KingOfTheHill/GUI/layouts/EventForeceEditor.edds";
    }
}