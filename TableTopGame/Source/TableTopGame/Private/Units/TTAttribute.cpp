// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Units/TTAttribute.h"
#include "TableTopGame.h"






void UTTAttribute::AddModifier(FAttribute AttributeStruct,FAttributeModifier mod){
	AttributeStruct.AddModifier(mod);
}

int32 UTTAttribute::RemoveModifier(FAttribute AttributeStruct,FAttributeModifier mod) {
	return AttributeStruct.RemoveModifier(mod);
}
