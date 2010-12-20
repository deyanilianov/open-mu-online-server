//=======================================================================================
//= NewsSystem.cpp
//=======================================================================================
#include "StdAfx.h"

//------------------------------------------------------
//- Variables
//------------------------------------------------------
gNewsSystem NewsSystem;
xNewsList NewsList[255];

//------------------------------------------------------
//- Start
//------------------------------------------------------
void gNewsSystem::Load()
{
	//--------------------------------------------------------------------------------
	FILE *fp;
	char sLineTxt[255] = {0};
	//--------------------------------------------------------------------------------
	this->Count = 0;
	//--------------------------------------------------------------------------------
	fp = fopen(INI_NEWS,"r");
	//--------------------------------------------------------------------------------
	if(!fp)
	{
		Tools.MessageBoxShow("File not found!","GMSystem.script not found!");
		Exit;
	}
	//--------------------------------------------------------------------------------
	rewind(fp);
	//--------------------------------------------------------------------------------
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		//--------------------------------------------------------------------------------
		if(sLineTxt[0] == '/')continue;
		if(sLineTxt[0] == ';')continue;
		//--------------------------------------------------------------------------------
		sscanf(sLineTxt, "%d %d %d %d %d %d %s",&this->Value[0],&this->Value[1],&this->Value[2],&this->Value[3],&this->Value[4],&this->Value[5],&this->String);
		//--------------------------------------------------------------------------------
		NewsList[this->Count].News_Day		= this->Value[0];
		NewsList[this->Count].News_Month	= this->Value[1];
		NewsList[this->Count].News_Year		= this->Value[2];
		NewsList[this->Count].News_Hour		= this->Value[3];
		NewsList[this->Count].News_Minute	= this->Value[4];
		NewsList[this->Count].News_Type		= this->Value[5];
		sprintf(NewsList[this->Count].News_Line,"%s",this->String);
		//--------------------------------------------------------------------------------
		this->Count++;
		//--------------------------------------------------------------------------------
		ZeroMemory(this->String,sizeof(this->String));
		//--------------------------------------------------------------------------------
	}
	//--------------------------------------------------------------------------------
	rewind(fp);
	fclose(fp);
	//--------------------------------------------------------------------------------
	Console.Write("[NewsSystem] News System has been loaded!");
	//--------------------------------------------------------------------------------
}
void Manage(void * lpParam)
{
	//--------------------------------------------------------------------------------
	while(true)
	{
		//--------------------------------------------------------------------------------
		SYSTEMTIME t;
		GetLocalTime(&t);
		//--------------------------------------------------------------------------------
		for(int x=1;x < NewsSystem.Count;x++)
		{
			//--------------------------------------------------------------------------------
			if(NewsList[NewsSystem.Count].News_Day == t.wDay && NewsList[NewsSystem.Count].News_Month == t.wMonth && NewsList[NewsSystem.Count].News_Year == t.wYear && NewsList[NewsSystem.Count].News_Hour == t.wHour && NewsList[NewsSystem.Count].News_Minute == t.wMinute)
			{
				//--------------------------------------------------------------------------------
				Player.SendAllTextMsg(NewsList[NewsSystem.Count].News_Type,NewsList[NewsSystem.Count].News_Line);
				//--------------------------------------------------------------------------------
				Console.Write("[NewsAncounce] Send Message: %s",NewsList[NewsSystem.Count].News_Line);
				//--------------------------------------------------------------------------------
			}
			//--------------------------------------------------------------------------------
		}
		//--------------------------------------------------------------------------------
		Sleep(100);
		//--------------------------------------------------------------------------------
	}
	//--------------------------------------------------------------------------------
	_endthread();
	//--------------------------------------------------------------------------------
}
void gNewsSystem::Start()
{
	if(ReadINI.GetInt("Main","NewsSystemEnabled",INI) == 1)
	{
		this->Load();
		_beginthread(Manage,0,NULL);
	}
}

//------------------------------------------------------
//- Variables
//------------------------------------------------------
extern gNewsSystem NewsSystem;