// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalSkill.h"
#include "AttackSkillBase.h"
#include "Engine/World.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ADecalSkill::ADecalSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	Circum = CreateDefaultSubobject<UDecalComponent>("Circum");
	Area = CreateDefaultSubobject<UDecalComponent>("Area");

	Circum->SetupAttachment(RootComponent);
	Area->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> mat
	(
		TEXT("Material'/Game/Texture/Mat_Circle.Mat_Circle'")
	);
	if (mat.Succeeded())
	{
		Mat = mat.Object;
	}

}


// Called when the game starts or when spawned
void ADecalSkill::BeginPlay()
{
	Super::BeginPlay();

	Circle_Instacne = UMaterialInstanceDynamic::Create(Mat, this, FName("circle_instance"));
	Area_Instacne = UMaterialInstanceDynamic::Create(Mat, this, FName("area_instance"));

	Circum->SetDecalMaterial(Circle_Instacne);
	Area->SetDecalMaterial(Area_Instacne);

	Circle_Instacne->SetScalarParameterValue("CircumArea1", 1.0f);
	Area_Instacne->SetScalarParameterValue("CircumArea1", 0.0f);

}


// Called every frame
void ADecalSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float DeltaTick = 0.5f / CastingTime;
	float current = 0.0f;
	Area_Instacne->GetScalarParameterValue(L"AreaValue",current);
	Area_Instacne->SetScalarParameterValue("AreaValue", current + DeltaTick * DeltaTime);
	if (current > 0.5f)
	{
		GetWorld()->SpawnActor<AActor>(SkillParticle,GetActorLocation(),GetActorRotation());
		Destroy();
	}
}

