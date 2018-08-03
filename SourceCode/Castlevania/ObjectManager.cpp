#include "ObjectManager.h"

ObjectManager* ObjectManager::instance = nullptr;
ObjectManager * ObjectManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new ObjectManager();
	}
	return instance;
}

void ObjectManager::init(TextureManager *textureM, Graphics *graphics)
{
	this->texttureManager = textureM;
	this->graphics = graphics;
}

void ObjectManager::onCheckCollision(BaseObject * obj, float frametime)
{

	for (list<BaseObject>::iterator i = object_list.begin(); i != object_list.end(); ++i)
	{
		obj->onCollision(&*(i), frametime);
	}
}

bool ObjectManager::load_list(const char * filename)
{
	VECTOR2 transform;
	if (this->camera)
		transform = VECTOR2(GAME_WIDTH * 0.5f - camera->getPosition().x, GAME_HEIGHT * 0.5f - camera->getPosition().y);
	try
	{
		ifstream ifs(filename);
		IStreamWrapper isw(ifs);
		Document jSon;
		jSon.ParseStream(isw);

		float x, y, height, width;
		//Load Wall position
		const Value& listWall = jSon["Wall"];
		if (listWall.IsArray())
		{
			BaseObject object(eID::WALL);
			Rect bound;

			for (SizeType i = 0; i < listWall.Size(); i++)
			{
				x = listWall[i]["x"].GetFloat();
				y = listWall[i]["y"].GetFloat();
				height = listWall[i]["height"].GetFloat();
				width = listWall[i]["width"].GetFloat();

				bound.left = x;
				bound.top = y;
				bound.right = bound.left + width;
				bound.bottom = bound.top + height;
				object.setBoundCollision(bound);

				object_list.push_back(object);
			}

		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::release()
{
	this->object_list.clear();
	delete instance;
}

void ObjectManager::setCamera(Camera *cam)
{
	this->camera = cam;
}