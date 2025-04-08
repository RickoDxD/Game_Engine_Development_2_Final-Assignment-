#include "World.hpp"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game, SceneNode::None))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f)
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(0)
{
}

void World::update(const GameTimer& gt)
{
	//mPlayerAircraft->setVelocity(0.0f, 0.0f);

	while (!mInputCommandQueue.isEmpty())
		mSceneGraph->onCommand(mInputCommandQueue.pop(), gt);

	//set boundary for scrolling background
	if (mBackground->getWorldPosition().z < -90)
		mBackground->setPosition(0, 0, 100.0);

	//adaptPlayerVelocity();
	mSceneGraph->update(gt);
	//mPlayerAircraft->update(gt);
	//mBackground->updateCurrent(gt);
}

void World::draw(Game* game)
{
	mSceneGraph->draw(game);
}

void World::buildScene(States::ID stateID)
{
	SceneNode* player = new SceneNode(mGame, SceneNode::Eagle);
	mPlayerAircraft = player;
	mPlayerAircraft->setPosition(0, 1, 0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	mSceneGraph->attachChild(mPlayerAircraft);


	SceneNode* enemy1 = new SceneNode(mGame, SceneNode::Raptor);
	auto raptor = enemy1;
	raptor->setPosition(-1, 1, 0);
	raptor->setScale(0.5, 0.5, 0.5);
	raptor->setWorldRotation(0, XM_PI, 0);
	mSceneGraph->attachChild(std::move(raptor));

	SceneNode* enemy2 = new SceneNode(mGame, SceneNode::Raptor);
	raptor = enemy2;
	raptor->setPosition(1, 1, 0);
	raptor->setScale(0.5, 0.5, 0.5);
	raptor->setWorldRotation(0, XM_PI, 0);
	mSceneGraph->attachChild(std::move(raptor));

	//scrolling background is now handled the same way as the aircraft class
	//std::unique_ptr<SceneNode> 
	SceneNode* backgroundSprite = new SceneNode(mGame, SceneNode::Background);
	mBackground = backgroundSprite;
	mBackground->setPosition(0, -5, 0);
	mBackground->setScale(100, 1, 100);
	mBackground->setVelocity(0.0f, - 0.5);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	LPCWSTR msgbuf = L"Game World building Scene\n";
	OutputDebugString(msgbuf);

	mSceneGraph->build(stateID);
}

XMVECTOR World::getPlayerPosition()
{
	return XMLoadFloat3(&mPlayerAircraft->getWorldPosition());
}

InputCommandQueue* World::getCommandQueue()
{
	return &mInputCommandQueue;
}

void World::adaptPlayerVelocity()
{
	XMFLOAT2 velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f) {
		velocity = XMFLOAT2(velocity.x / std::sqrt(2.f), velocity.y / std::sqrt(2.f));
		mPlayerAircraft->setVelocity(velocity);
	}
}
