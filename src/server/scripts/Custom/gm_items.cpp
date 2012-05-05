#include "ScriptPCH.h"

// Change this value to the minimum security level required to get the items
#define MIN_GM_LEVEL 1

class GMItems : public PlayerScript
{
    public:

        GMItems() : PlayerScript("GM_Items"){}
		uint64 playerGUID;
		void OnCreate(Player * player)
		{
			playerGUID = player->GetGUID();
		}

		void OnLogin(Player* player)
		{
			if (playerGUID == player->GetGUID())
			{
				QueryResult account = CharacterDatabase.PQuery("SELECT * FROM characters WHERE guid = '%u'", playerGUID);
				Field * accID = account->Fetch();
				QueryResult gmaccount = LoginDatabase.PQuery("SELECT * FROM account_access WHERE id = '%u' AND gmlevel >= '%u'", accID[1].GetInt32(), MIN_GM_LEVEL);
				if (gmaccount)
				{
					player->AddItem(12064, 1);
					player->AddItem(2586, 1);
					player->AddItem(11508, 1);
					playerGUID = 0;
				}
			}
		}


};

void AddSC_GMItems()
{
	new GMItems();
}