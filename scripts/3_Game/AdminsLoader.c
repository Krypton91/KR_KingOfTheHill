class KR_KingOfTheHillPermisionService
{
    protected autoptr TStringArray  m_Admins;
    protected FileHandle            m_FileHandler;
    void KR_KingOfTheHillPermisionService()
    {
        if(!FileExist("$profile:KingOfTheHill"))
            MakeDirectory("$profile:KingOfTheHill");
        
        if(!FileExist("$profile:KingOfTheHill/Objects"))
            MakeDirectory("$profile:KingOfTheHill/Objects");
        
        if(!FileExist("$profile:KingOfTheHill/Admins"))
            MakeDirectory("$profile:KingOfTheHill/Admins");

        m_Admins = new autoptr TStringArray;

        CheckForAdminFile();
    }

    TStringArray GetAdmins()
    {
        return this.m_Admins;
    }

    bool IsAdmin(string SteamId)
    {
        return m_Admins.Find(SteamId) != -1;
    }

    void CheckForAdminFile()
    {
        if(!FileExist("$profile:KingOfTheHill/Admins/Admins.txt"))
            CreateAdminFile();

        ReadAdminFile();
    }

    void CreateAdminFile()
    {
        if(!m_FileHandler || m_FileHandler == 0)
        {
            m_FileHandler = OpenFile("$profile:KingOfTheHill/Admins/Admins.txt", FileMode.WRITE);
            if(m_FileHandler != 0)
            {
                FPrintln(m_FileHandler, "86842348271742921 //Admin Micheal");
                FPrintln(m_FileHandler, "86842358271742922 //Admin Brunno");
            }
            else
            {
                Error("[KOTH] -> Can not create default Admin.txt!");
            }

            CloseFile(m_FileHandler);
        }
    }

    void ReadAdminFile()
    {
        m_Admins.Clear();
        m_FileHandler = OpenFile("$profile:KingOfTheHill/Admins/Admins.txt", FileMode.READ);
        if(m_FileHandler != 0)
        {
            string line_content;
            while ( FGets(m_FileHandler,  line_content ) > 0 )
            {
                string result = CheckLineForSteamId(line_content);
                m_Admins.Insert(result);
            }
            CloseFile(m_FileHandler);
        }
        else
        {
            Error("[KOTH] -> Can not open Admins.txt");
        }
    }

    string CheckLineForSteamId(string Line)
    {
        Line = Line.Trim();
        string steamid = Line.Substring(0, 17);
        return steamid;
    }
}