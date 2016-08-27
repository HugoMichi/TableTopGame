// Fill out your copyright notice in the Description page of Project Settings.

#include "TableTopGame.h"
#include "Public/Units/TTAttribute.h"





void UTTAttribute::AddModifier(FAttribute AttributeStruct,FAttributeModifier mod){
AttributeStruct.AddModifier(mod);
}

int32 UTTAttribute::RemoveModifier(FAttribute AttributeStruct,FAttributeModifier mod) {
return AttributeStruct.RemoveModifier(mod);
}
