// Fill out your copyright notice in the Description page of Project Settings.


#include "LCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALCharacter::ALCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	SpringArmComp->bUsePawnControlRotation=true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractComponent = CreateDefaultSubobject<UInteractComponent>("Interact Comp");

	AttributeComp=CreateDefaultSubobject<UAttributeComponent>("AttributeComp");

	ActionComponent=CreateDefaultSubobject<ULActionComponent>("ActionComp");

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	

}

// Called when the game starts or when spawned
void ALCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALCharacter::MoveForward(float Value)
{
	FRotator contrRot = GetControlRotation();
	contrRot.Roll = 0.0f;
	contrRot.Pitch = 0.0f;
	AddMovementInput(contrRot.Vector(),Value);
}

void ALCharacter::MoveRight(float value)
{
	FRotator contrRot = GetControlRotation();
	contrRot.Roll = 0.0f;
	contrRot.Pitch = 0.0f;

	FVector RightVector = FRotationMatrix(contrRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,value);
}



void ALCharacter::Jump()
{
	Super::Jump();
}

void ALCharacter::SprintStart()
{
	ActionComponent->StartActionByName(this,"Sprint");
}

void ALCharacter::SprintStop()
{
	ActionComponent->StopActionByName(this,"Sprint");
}

void ALCharacter::PrimaryInteract()
{
	InteractComponent->PrimaryInteract();
}




// Called every frame
void ALCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ALCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ALCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("PrimaryAttack",EInputEvent::IE_Pressed,this,&ALCharacter::PrimartAttack);
	PlayerInputComponent->BindAction("BlackHoleAttack",EInputEvent::IE_Pressed,this,&ALCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("Teleport",EInputEvent::IE_Pressed,this,&ALCharacter::TeleportSkill);
	PlayerInputComponent->BindAction("Jump",EInputEvent::IE_Pressed,this,&ALCharacter::Jump);
	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&ALCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&ALCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&ALCharacter::SprintStop);
}




void ALCharacter::OnheathChange(AActor* instigatorActor, UAttributeComponent* owningComp, float newheath, float delta)
{
	if(newheath<=0&& delta<0)
	{
		APlayerController * PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
		SetActorEnableCollision(false);
	}

	if(delta<0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
	}
}

void ALCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this,&ALCharacter::OnheathChange);
}

void ALCharacter::HealSelf(float count /* = 100 */)
{
	AttributeComp->ApplyHealthChange(this,count);
}

FVector ALCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}


void ALCharacter::PrimartAttack()
{
	ActionComponent->StartActionByName(this,"PrimaryAttack");
}


void ALCharacter::BlackHoleAttack()
{
	ActionComponent->StartActionByName(this,"TelePort");
}


void ALCharacter::TeleportSkill()
{
	ActionComponent->StartActionByName(this,"BlackHole");
}