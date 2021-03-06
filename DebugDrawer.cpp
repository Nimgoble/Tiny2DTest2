#include "DebugDrawer.h"
#include "ThirdParty\Tiny2D\Include\Tiny2D.h"
#include "T2DTVec2D.h"
#include "T2DTColorHelper.h"

using namespace Tiny2D;
void DebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	//Tiny2D::Shape::DrawParams params;
	//params.color = Tiny2D::Color::Red;//T2DTColorHelper::GetTiny2DColorFromBox2DColor(color);
	//params.SetNumVerts(vertexCount);
	//params.SetGeometryType(Shape::Geometry::Type_Lines);

	//std::vector<float> xy;
	//for (int i = 0; i < vertexCount; i++) 
	//{
	//	const b2Vec2 &vec = vertices[i];
	//	xy.push_back(vec.x * 32.0f);
	//	xy.push_back(vec.y * 32.0f);
 //   }
	//params.SetPosition(&xy[0]);

	//Shape::Draw(&params);

	//std::vector<Tiny2D::Vec2> xy;
	for (int i = 0; (i + 1) < vertexCount; ++i) 
	{
		Tiny2D::Shape::DrawLine(T2DTVec2D::FromBox2DVec(vertices[i]), T2DTVec2D::FromBox2DVec(vertices[i + 1]), Tiny2D::Color::Red);
		//xy.push_back(T2DTVec2D::FromBox2DVec(vertices[i]));
		//xy.push_back(T2DTVec2D::FromBox2DVec(vertices[i + 1]));
    }
	//Line between the last vertex and the first
	Tiny2D::Shape::DrawLine(T2DTVec2D::FromBox2DVec(vertices[vertexCount - 1]), T2DTVec2D::FromBox2DVec(vertices[0]), Tiny2D::Color::Red);
	/*xy.push_back(T2DTVec2D::FromBox2DVec(vertices[vertexCount - 1]));
	xy.push_back(T2DTVec2D::FromBox2DVec(vertices[0]));

	Tiny2D::Shape::DrawLines(&xy[0], vertexCount / 2, Tiny2D::Color::Red);*/
}
void DebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Tiny2D::Shape::DrawParams params;
	params.color = Tiny2D::Color::Green;
	params.color.a = 0.5f;//T2DTColorHelper::GetTiny2DColorFromBox2DColor(color);
	params.SetNumVerts(vertexCount);
	params.SetGeometryType(Shape::Geometry::Type_TriangleFan);

	std::vector<float> xy;
	for (int i = 0; i < vertexCount; i++) 
	{
		const b2Vec2 &vec = vertices[i];
		xy.push_back(vec.x * 32.0f);
		xy.push_back(vec.y * 32.0f);
    }
	params.SetPosition(&xy[0]);

	Shape::Draw(&params);
}
void DebugDrawer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	Shape::DrawCircle(T2DTVec2D::FromBox2DVec(center), radius, 12, 0.0f, T2DTColorHelper::GetTiny2DColorFromBox2DColor(color));
}
void DebugDrawer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	Shape::DrawCircle(T2DTVec2D::FromBox2DVec(center), radius, 12, 0.0f, T2DTColorHelper::GetTiny2DColorFromBox2DColor(color));
}
void DebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	Shape::DrawLine(T2DTVec2D::FromBox2DVec(p1), T2DTVec2D::FromBox2DVec(p2), T2DTColorHelper::GetTiny2DColorFromBox2DColor(color));
}
void DebugDrawer::DrawTransform(const b2Transform& xf)
{
	/*sf::RectangleShape shape(sf::Vector3f(1.0f, 1.0f));
	shape.setPosition(B2VecToSFMLVec(xf.p));
	shape.setFillColor(sf::Color::White);
	target->draw(shape);*/
}