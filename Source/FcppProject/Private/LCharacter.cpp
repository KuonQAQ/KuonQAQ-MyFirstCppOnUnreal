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

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	ShootSocket = "Muzzle_01";

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
}

void ALCharacter::TimerHandle_PrimaryAttackEvent()
{
	SpawnProjectile(ProjectileClass);
}




void ALCharacter::PrimartAttack()
{
	PlayAnimMontage(AttackAnim);

	UGameplayStatics::SpawnEmitterAttached(ImpactVFx,GetMesh(),ShootSocket,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ALCharacter::TimerHandle_PrimaryAttackEvent,0.2f);
	
	
}



void ALCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if(ensureAlways(ClassToSpawn))
	{
		FVector Handlocation = GetMesh()->GetSocketLocation(ShootSocket);

		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart+(GetControlRotation().Vector()*5000);

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams objparams;
		objparams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objparams.AddObjectTypesToQuery(ECC_WorldStatic);
		objparams.AddObjectTypesToQuery(ECC_Pawn);

		FHitResult HitResult;

		if(GetWorld()->SweepSingleByObjectType(HitResult,TraceStart,TraceEnd,FQuat::Identity,objparams,Shape,Params))
		{
			TraceEnd=HitResult.ImpactPoint;
		}

		FRotator ProjectileRotator = FRotationMatrix::MakeFromX(TraceEnd-Handlocation).Rotator();
		
		FTransform SpawnTrans = FTransform(ProjectileRotator,Handlocation);

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParam.Instigator= this;
	
		GetWorld()->SpawnActor<AActor>(ClassToSpawn,SpawnTrans,SpawnParam);
	}
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

void ALCharacter::BlackHoleAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack,this,&ALCharacter::TimerHandle_BlackHoleAttackEvent,0.2f);
}



void ALCharacter::TimerHandle_BlackHoleAttackEvent()
{
	SpawnProjectile(BlackHoleProjectile);
}

void ALCharacter::Timehandle_TeleportSkillEvent()
{
	SpawnProjectile(DashProjectile);
}

void ALCharacter::TeleportSkill()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportSkill,this,&ALCharacter::Timehandle_TeleportSkillEvent,0.2f);
}