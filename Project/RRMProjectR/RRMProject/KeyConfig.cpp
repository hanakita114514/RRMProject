#include "KeyConfig.h"
#include <RRMLib.h>
#include <stdio.h>

KeyConfig::KeyConfig()
{
}


KeyConfig::~KeyConfig()
{
}

void
KeyConfig::Save(KeyData& keyData)
{
	FILE* fp;
	fp = fopen("Resource/data/save/KeyConfig.dat", "wb");
	fwrite(&keyData, sizeof(KeyData), 1, fp);
	fclose(fp);
}

void
KeyConfig::Load(KeyData& keyData)
{
	FILE* fp;
	fp = fopen("Resource/data/save/KeyConfig.dat", "rb");

	if (fp == nullptr)
	{
		Save(keyData);
		return;
	}

	KeyData kd;
	fread(&kd, sizeof(KeyData), 1, fp);
	fclose(fp);

	keyData = kd;
}