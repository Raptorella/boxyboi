#include "Box.h"
IndexedTriangleList<Vec2> Box::model; //TODO: what is this?


class RedTrait : public Box::ColorTrait
{
public:
	std::unique_ptr<ColorTrait> Clone() const override
	{
		return std::make_unique<RedTrait>();
	}
	Color GetColor() const override
	{
		return Colors::Red;
	}
};

class GreenTrait : public Box::ColorTrait
{
public:
	std::unique_ptr<ColorTrait> Clone() const override
	{
		return std::make_unique<GreenTrait>();
	}
	Color GetColor() const override
	{
		return Colors::Green;
	}
};

class BlueTrait : public Box::ColorTrait
{
public:
	std::unique_ptr<ColorTrait> Clone() const override
	{
		return std::make_unique<BlueTrait>();
	}
	Color GetColor() const override
	{
		return Colors::Blue;
	}
};

class YellowTrait : public Box::ColorTrait
{
public:
	std::unique_ptr<ColorTrait> Clone() const override
	{
		return std::make_unique<YellowTrait>();
	}
	Color GetColor() const override
	{
		return Colors::Yellow;
	}
};

class WhiteTrait : public Box::ColorTrait
{
public:
	std::unique_ptr<ColorTrait> Clone() const override
	{
		return std::make_unique<WhiteTrait>();
	}
	Color GetColor() const override
	{
		return Colors::White;
	}
};

std::unique_ptr<Box> Box::Spawn( float size,const Boundaries& bounds,b2World& world,std::mt19937& rng )
{
	std::uniform_real_distribution<float> pos_dist(
		-bounds.GetSize() + size * 2.0f,
		bounds.GetSize() - size * 2.0f
	);
	std::uniform_real_distribution<float> power_dist( 0.0f,6.0f );
	std::uniform_real_distribution<float> angle_dist( -PI,PI );
	std::uniform_int_distribution<int> type_dist( 0,4 );

	const auto linVel = (Vec2{ 1.9f,0.0f } * Mat2::Rotation( angle_dist( rng ) )) * power_dist( rng );
	const auto pos = Vec2{ pos_dist( rng ),pos_dist( rng ) };
	const auto ang = angle_dist( rng );
	const auto angVel = angle_dist( rng ) * 1.5f;

	std::unique_ptr<ColorTrait> pColorTrait;
	switch( type_dist( rng ) )
	{
	case 0:
		pColorTrait = std::make_unique<RedTrait>();
		break;
	case 1:
		pColorTrait = std::make_unique<GreenTrait>();
		break;
	case 2:
		pColorTrait = std::make_unique<BlueTrait>();
		break;
	case 3:
		pColorTrait = std::make_unique<WhiteTrait>();
		break;
	case 4:
		pColorTrait = std::make_unique<YellowTrait>();
		break;
	}
	
	return std::make_unique<Box>( std::move( pColorTrait ),world,pos,size,ang,linVel,angVel );
}

bool Box::GetShouldSplit()
{
	return shouldSplit;
}

void Box::SetShouldSplit(bool b)
{
	shouldSplit = b;
}

std::vector<std::unique_ptr<Box>> Box::Split(b2World& world)
{
	float daSize = size;
	float newSize = daSize / 2;
	Vec2 posThis = Vec2(pBody->GetPosition());
	Vec2 posRightUp = posThis + Vec2{daSize/4, daSize/4};
	Vec2 posLeftUp = posThis + Vec2{ -daSize / 4, daSize / 4 };
	Vec2 posRightBottom = posThis + Vec2{ daSize / 4, -daSize / 4 };
	Vec2 posLeftBottom = posThis + Vec2{ -daSize / 4, -daSize / 4 };
	auto aColorTrait = pColorTrait->Clone();
	auto bColorTrait = pColorTrait->Clone();
	auto cColorTrait = pColorTrait->Clone();


	std::vector<std::unique_ptr<Box>> boxes;
	boxes.emplace_back(std::make_unique<Box>(std::move(pColorTrait), world, posRightUp, newSize));
	boxes.emplace_back(std::make_unique<Box>(std::move(aColorTrait), world, posLeftUp, newSize));
	boxes.emplace_back(std::make_unique<Box>(std::move(bColorTrait), world, posRightBottom, newSize));
	boxes.emplace_back(std::make_unique<Box>(std::move(cColorTrait), world, posLeftBottom, newSize));
	return boxes;
}
