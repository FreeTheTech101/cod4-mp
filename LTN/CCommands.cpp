#include "stdafx.h"

// NOT WORKING, AND I WANT TO SLEEP.

// -------------------------------------------------

CCommands::CCommands()
{
	cmd_functions = (cmd_function_t*)COffsets::VAR_cmd_functions;
}

// -------------------------------------------------

cmd_function_t* CCommands::FindCommand(const char* name)
{
	/*DWORD dwFunc = COffsets::FUNC_Cmd_FindCommand;

	__asm push name;
	__asm call dwFunc;
	__asm add esp, 4h;

	__asm test eax, eax;
	__asm retn;*/
	return 0;
}

// -------------------------------------------------

void CCommands::AddCommand(const char* name, xcommand_t function)
{
	// Ugly call to Cmd_FindCommand
	if (((cmd_function_t*(*)(const char*))COffsets::FUNC_Cmd_FindCommand)(name))
	{
		if (function != NULL)
			CGame::Printf(16, "Cmd_AddCommand: %s already defined\n", name);
		return;
	}

	cmd_function_t* cmd = (cmd_function_t*)malloc(sizeof(struct cmd_function_s));

	cmd->name = (char*)name;
	cmd->function = function;
	cmd->next = cmd_functions;
	cmd_functions = cmd;


}