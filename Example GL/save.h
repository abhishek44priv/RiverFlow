#pragma once
#include"stdafx.h"
class RfShape
{
public:
	RfColor color = RfColor::Black;
};
class RfLine :public RfShape
{
public:
	RfVector2 a, b;
public:
	RfLine(RfVector2 a, RfVector2 b)
	{
		this->a = a;
		this->b = b;
	}
};
class RfRectangle :public RfShape
{
public:
	RfRect r;
public:
	RfRectangle(RfRect r)
	{
		this->r = r;
	}
};
class RfTriangle :public RfShape
{
public:
	RfVector2 a, b, c;
public:
	RfTriangle(RfVector2 a, RfVector2 b, RfVector2 c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
};
class RfPolygon :public RfShape
{

};
class RfEllipse :public RfShape
{

};
/*--------------------------------------------------------------*/
class RfMat33
{
public:
	float out[9];
public:
	RfMat33()
	{
		MakeIdentity();
	}
	void MakeIdentity()
	{
		out[0] = 1;
		out[1] = 0;
		out[2] = 0;
		out[3] = 0;
		out[4] = 1;
		out[5] = 0;
		out[6] = 0;
		out[7] = 0;
		out[8] = 1;
	}
	void MakeTranspose()
	{
		float a01 = out[1],
			a02 = out[2],
			a12 = out[5];
		out[1] = out[3];
		out[2] = out[6];
		out[3] = a01;
		out[5] = out[7];
		out[6] = a02;
		out[7] = a12;
	}
	void Multiply(RfMat33 b)
	{
		float a00 = out[0],
			a01 = out[1],
			a02 = out[2];
		float a10 = out[3],
			a11 = out[4],
			a12 = out[5];
		float a20 = out[6],
			a21 = out[7],
			a22 = out[8];
		float b00 = b.out[0],
			b01 = b.out[1],
			b02 = b.out[2];
		float b10 = b.out[3],
			b11 = b.out[4],
			b12 = b.out[5];
		float b20 = b.out[6],
			b21 = b.out[7],
			b22 = b.out[8];
		out[0] = b00 * a00 + b01 * a10 + b02 * a20;
		out[1] = b00 * a01 + b01 * a11 + b02 * a21;
		out[2] = b00 * a02 + b01 * a12 + b02 * a22;
		out[3] = b10 * a00 + b11 * a10 + b12 * a20;
		out[4] = b10 * a01 + b11 * a11 + b12 * a21;
		out[5] = b10 * a02 + b11 * a12 + b12 * a22;
		out[6] = b20 * a00 + b21 * a10 + b22 * a20;
		out[7] = b20 * a01 + b21 * a11 + b22 * a21;
		out[8] = b20 * a02 + b21 * a12 + b22 * a22;
	}
	void Translate(RfVector2 v)
	{
		float a00 = out[0],
			a01 = out[1],
			a02 = out[2],
			a10 = out[3],
			a11 = out[4],
			a12 = out[5],
			a20 = out[6],
			a21 = out[7],
			a22 = out[8],
			x = v.x,
			y = v.y;
		out[0] = a00;
		out[1] = a01;
		out[2] = a02;
		out[3] = a10;
		out[4] = a11;
		out[5] = a12;
		out[6] = x * a00 + y * a10 + a20;
		out[7] = x * a01 + y * a11 + a21;
		out[8] = x * a02 + y * a12 + a22;
	}
	void Rotate(float rad)
	{
		float a00 = out[0],
			a01 = out[1],
			a02 = out[2],
			a10 = out[3],
			a11 = out[4],
			a12 = out[5],
			a20 = out[6],
			a21 = out[7],
			a22 = out[8],
			s = RfMath::Sin(rad),
			c = RfMath::Cos(rad);
		out[0] = c * a00 + s * a10;
		out[1] = c * a01 + s * a11;
		out[2] = c * a02 + s * a12;
		out[3] = c * a10 - s * a00;
		out[4] = c * a11 - s * a01;
		out[5] = c * a12 - s * a02;
		out[6] = a20;
		out[7] = a21;
		out[8] = a22;
	}
	void Scale(RfVector2 v)
	{
		float x = v.x,
			y = v.y;
		out[0] = x * out[0];
		out[1] = x * out[1];
		out[2] = x * out[2];
		out[3] = y * out[3];
		out[4] = y * out[4];
		out[5] = y * out[5];
		out[6] = out[6];
		out[7] = out[7];
		out[8] = out[8];
	}
	void MakeProjection(RfSize size)
	{
		out[0] = 2 / size.width;
		out[1] = 0;
		out[2] = 0;
		out[3] = 0;
		out[4] = 2 / size.height;
		out[5] = 0;
		out[6] = 0;
		out[7] = 0;
		out[8] = 1;
	}
};
class RfMat33_2
{
public:
	float dst[9];
public:
	RfMat33_2()
	{
		Identity();
	}
	void Print()
	{
		print("{} {} {} \n", dst[0], dst[1], dst[2]);
		print("{} {} {} \n", dst[3], dst[4], dst[5]);
		print("{} {} {} \n", dst[6], dst[7], dst[8]);
	}
	static RfMat33_2  Multiply_(RfMat33_2 a, RfMat33_2 b)
	{
		RfMat33_2 mat;
		float a00 = a.dst[0 * 3 + 0];
		float a01 = a.dst[0 * 3 + 1];
		float a02 = a.dst[0 * 3 + 2];
		float a10 = a.dst[1 * 3 + 0];
		float a11 = a.dst[1 * 3 + 1];
		float a12 = a.dst[1 * 3 + 2];
		float a20 = a.dst[2 * 3 + 0];
		float a21 = a.dst[2 * 3 + 1];
		float a22 = a.dst[2 * 3 + 2];
		float b00 = b.dst[0 * 3 + 0];
		float b01 = b.dst[0 * 3 + 1];
		float b02 = b.dst[0 * 3 + 2];
		float b10 = b.dst[1 * 3 + 0];
		float b11 = b.dst[1 * 3 + 1];
		float b12 = b.dst[1 * 3 + 2];
		float b20 = b.dst[2 * 3 + 0];
		float b21 = b.dst[2 * 3 + 1];
		float b22 = b.dst[2 * 3 + 2];

		mat.dst[0] = b00 * a00 + b01 * a10 + b02 * a20;
		mat.dst[1] = b00 * a01 + b01 * a11 + b02 * a21;
		mat.dst[2] = b00 * a02 + b01 * a12 + b02 * a22;
		mat.dst[3] = b10 * a00 + b11 * a10 + b12 * a20;
		mat.dst[4] = b10 * a01 + b11 * a11 + b12 * a21;
		mat.dst[5] = b10 * a02 + b11 * a12 + b12 * a22;
		mat.dst[6] = b20 * a00 + b21 * a10 + b22 * a20;
		mat.dst[7] = b20 * a01 + b21 * a11 + b22 * a21;
		mat.dst[8] = b20 * a02 + b21 * a12 + b22 * a22;
		return mat;
	}
	void Identity()
	{
		dst[0] = 1;
		dst[1] = 0;
		dst[2] = 0;
		dst[3] = 0;
		dst[4] = 1;
		dst[5] = 0;
		dst[6] = 0;
		dst[7] = 0;
		dst[8] = 1;
	}
	void Project(float width, float height)
	{
		auto res = Multiply_(*this, Projection_(width, height));
		*this = res;
	}
	void Translate(float tx, float ty)
	{
		auto res = Multiply_(*this, Translation_(tx, ty));
		*this = res;
	}
	void Rotate(float rad)
	{
		auto res = Multiply_(*this, Rotation_(rad));
		*this = res;
	}
	void Scale(float sx, float sy)
	{
		auto res = Multiply_(*this, Scaling_(sx, sy));
		*this = res;
	}
	static RfMat33_2 Projection_(float width, float height)
	{
		RfMat33_2 mat;
		auto& dst = mat.dst;
		dst[0] = 2 / width;
		dst[1] = 0;
		dst[2] = 0;
		dst[3] = 0;
		dst[4] = -2 / height;
		dst[5] = 0;
		dst[6] = -1;
		dst[7] = 1;
		dst[8] = 1;
		return mat;
	}
	static RfMat33_2 Translation_(float tx, float ty)
	{
		RfMat33_2 mat;
		auto& dst = mat.dst;
		dst[0] = 1;
		dst[1] = 0;
		dst[2] = 0;
		dst[3] = 0;
		dst[4] = 1;
		dst[5] = 0;
		dst[6] = tx;
		dst[7] = ty;
		dst[8] = 1;
		return mat;
	}
	static RfMat33_2 Rotation_(float deg)
	{
		RfMat33_2 mat;
		float c = RfMath::Cos(deg);
		float s = RfMath::Sin(deg);
		auto& dst = mat.dst;
		dst[0] = c;
		dst[1] = -s;
		dst[2] = 0;
		dst[3] = s;
		dst[4] = c;
		dst[5] = 0;
		dst[6] = 0;
		dst[7] = 0;
		dst[8] = 1;
		return mat;
	}
	static RfMat33_2 Scaling_(float sx, float sy)
	{
		RfMat33_2 mat;
		auto& dst = mat.dst;
		dst[0] = sx;
		dst[1] = 0;
		dst[2] = 0;
		dst[3] = 0;
		dst[4] = sy;
		dst[5] = 0;
		dst[6] = 0;
		dst[7] = 0;
		dst[8] = 1;
		return mat;
	}
	static RfVector2 TransformPoint_(RfVector2 p, RfMat33_2 mat)
	{
		float v0 = p.x;
		float v1 = p.y;
		auto& m = mat.dst;
		float d = v0 * m[0 * 3 + 2] + v1 * m[1 * 3 + 2] + m[2 * 3 + 2];
		return{
			(v0 * m[0 * 3 + 0] + v1 * m[1 * 3 + 0] + m[2 * 3 + 0]) / d,
				(v0 * m[0 * 3 + 1] + v1 * m[1 * 3 + 1] + m[2 * 3 + 1]) / d,
		};
	}
	static RfMat33_2 Inverse_(RfMat33_2 mat)
	{
		float m00 = mat.dst[0 * 3 + 0];
		float m01 = mat.dst[0 * 3 + 1];
		float m02 = mat.dst[0 * 3 + 2];
		float m10 = mat.dst[1 * 3 + 0];
		float m11 = mat.dst[1 * 3 + 1];
		float m12 = mat.dst[1 * 3 + 2];
		float m20 = mat.dst[2 * 3 + 0];
		float m21 = mat.dst[2 * 3 + 1];
		float m22 = mat.dst[2 * 3 + 2];

		float b01 = m22 * m11 - m12 * m21;
		float b11 = -m22 * m10 + m12 * m20;
		float b21 = m21 * m10 - m11 * m20;

		float det = m00 * b01 + m01 * b11 + m02 * b21;
		float invDet = 1.0f / det;
		RfMat33_2 out;
		auto& dst = out.dst;

		dst[0] = b01 * invDet;
		dst[1] = (-m22 * m01 + m02 * m21) * invDet;
		dst[2] = (m12 * m01 - m02 * m11) * invDet;
		dst[3] = b11 * invDet;
		dst[4] = (m22 * m00 - m02 * m20) * invDet;
		dst[5] = (-m12 * m00 + m02 * m10) * invDet;
		dst[6] = b21 * invDet;
		dst[7] = (-m21 * m00 + m01 * m20) * invDet;
		dst[8] = (m11 * m00 - m01 * m10) * invDet;

		return out;
	}
};
/*------------------------------------------------------------*/
using std::vector;
struct RfVertex
{
	RfVector2 v;
	RfColor::RfColorF color;
};
class RfDArray
{

};
class RfDrawList
{
public:
	vector<RfVertex> vertices;
	vector<unsigned int> indices;

	vector<RfVertex> lineVertices;
	vector<unsigned int> lineIndices;

	float tx = 0, ty = 0;
	float sx = 1.0f, sy = 1.0f;
	float rad = 0.0f;
	float sint = RfMath::Sin(rad);
	float cost = RfMath::Cos(rad);
private:
	void Transform(RfVector2& p)
	{
		p.x *= sx;
		p.y *= sy;
		float tempX = p.x;
		p.x = (p.x * cost - p.y * sint) + tx;
		p.y = (p.y * cost + tempX * sint) + ty;
	}

public:
	void Clear()
	{
		vertices.clear();
		indices.clear();
	}

	void AddTriangle(float size, RfColor color)
	{
		auto lastSize = (UINT)vertices.size();

		const float x = size * 0.866f;
		const float y = size * 0.500f;

		RfVector2 p1 = { 0,size };
		RfVector2 p2 = { -x ,-y };
		RfVector2 p3 = { x ,-y };

		Transform(p1);
		Transform(p2);
		Transform(p3);

		vertices.push_back({ p1,color.ToRfColorF() });
		vertices.push_back({ p2,color.ToRfColorF() });
		vertices.push_back({ p3,color.ToRfColorF() });

		indices.push_back(lastSize + 0);
		indices.push_back(lastSize + 1);
		indices.push_back(lastSize + 2);
	}
	void AddTriangle(RfVector2 a, RfVector2 b, RfVector2 c, RfColor color)
	{
		auto lastSize = (UINT)vertices.size();

		a.Plus({ tx,ty });
		b.Plus({ tx,ty });
		c.Plus({ tx,ty });

		vertices.push_back({ a,color.ToRfColorF() });
		vertices.push_back({ b,color.ToRfColorF() });
		vertices.push_back({ c,color.ToRfColorF() });

		indices.push_back(lastSize + 0);
		indices.push_back(lastSize + 1);
		indices.push_back(lastSize + 2);
	}
	void AddLine(RfVector2 a, RfVector2 b, float thick, RfColor color)
	{
		auto ba = b - a;
		ba.Normalize();
		ba *= thick;

		auto norm = ba.GetNormal();
		//ba.Rotate(RfMath::Deg2Rad * 90);

		auto v1 = a + norm * (1.0f, -1.0f);
		auto v2 = b + norm * (1.0f, -1.0f);
		auto v3 = b + norm;
		auto v4 = a + norm;

		auto lastSize = (UINT)vertices.size();

		vertices.push_back({ v1,color.ToRfColorF() });
		vertices.push_back({ v2,color.ToRfColorF() });
		vertices.push_back({ v3,color.ToRfColorF() });
		vertices.push_back({ v4,color.ToRfColorF() });

		indices.push_back(lastSize + 0);
		indices.push_back(lastSize + 1);
		indices.push_back(lastSize + 2);

		indices.push_back(lastSize + 0);
		indices.push_back(lastSize + 2);
		indices.push_back(lastSize + 3);
	}
	void AddLines(vector<RfVertex>& vertices, float thick)
	{

	}
	void AddRect(RfSize size, RfColor color)
	{
		auto a = RfVector2(-size.width, size.height);
		auto b = RfVector2(size.width, size.height);
		auto c = RfVector2(size.width, -size.height);
		auto d = RfVector2(-size.width, -size.height);

	}
	void Translate(float x, float y)
	{
		tx = x;
		ty = y;
	}
	void Rotate(float rad)
	{
		this->rad = rad;
		sint = RfMath::Sin(rad);
		cost = RfMath::Cos(rad);
	}
	void Scale(float sx, float sy)
	{
		this->sx = sx;
		this->sy = sy;
	}
};
class RfGLDrawListRender
{
	unsigned int VBO, VAO, EBO, countTriangles;
	RfGLShaderCompiler shader;

public:
	void Init()
	{
		shader.CreateFromFile("res\\shader\\simple");
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(RfVertex),
			0, GL_STREAM_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int),
			0, GL_STREAM_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
	void Update(RfDrawList& drawList)
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, drawList.vertices.size() * sizeof(RfVertex),
			drawList.vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawList.indices.size() * sizeof(unsigned int),
			drawList.indices.data(), GL_STATIC_DRAW);

		countTriangles = (UINT)drawList.indices.size();
	}
	void Draw()
	{
		shader.use();
		glBindVertexArray(VAO);
		GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
		shader.setVec2("screen", (float)last_viewport[2] / 2.0f, (float)last_viewport[3] / 2.0f);
		glDrawElements(GL_TRIANGLES, countTriangles, GL_UNSIGNED_INT, 0);
	}

};
/*---------------------------------------*/
struct RfCamera2d
{

};
/*---------------------------------------------------------------*/
class Example :public RfGLWindow
{
	RfDrawList render;
	RfGLDrawListRender drawListRender;
	RfVector2 mousep;
	vector<RfVector2> randPoints;
	vector<RfColor> randColors;
	float speed = 0;
public:
	Example()
	{
		Animate(60);
		{
#define rr RfRandom::RangeFloat(-500,500)
#define ddd RfRandom::RangeInt(0,255)
#define cc RfColor(ddd,ddd,ddd,ddd)
		}

		{
			drawListRender.Init();
			repeat_for(100000)
			{
				randPoints.push_back({ rr ,rr });
				randColors.push_back(cc);
			}
		}
	}
protected:
	void OnMouseMove(RfMouseEvent& e)override
	{
		mousep.Set((float)e.x - (GetWidth() / 2.0f), -(float)e.y + (GetHeight() / 2.0f));

	}
	void OnSize(RfSizeEvent& e)override
	{
		RfGLWindow::OnSize(e);
	}
	void OnPaint() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		render.Clear();

		repeat_for(10000)
		{
			auto& p = randPoints[i];
			render.Translate(p.x, p.y);
			render.AddTriangle(5, randColors[i]);
		}
		drawListRender.Update(render);
		drawListRender.Draw();
		render.rad += speed;
		SwapBuffer();

	}
};
class  Example2 :public RfGLWindow
{
	class RfGLDrawListRender
	{
		unsigned int VBO, VAO, EBO, countTriangles;
		RfGLShaderCompiler shader;

	public:
		void Init()
		{
			shader.CreateFromFile("res\\shader\\camera1");
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(RfVertex),
				0, GL_STREAM_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int),
				0, GL_STREAM_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
		}
		void Update(RfDrawList& drawList)
		{
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, drawList.vertices.size() * sizeof(RfVertex),
				drawList.vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawList.indices.size() * sizeof(unsigned int),
				drawList.indices.data(), GL_STATIC_DRAW);

			countTriangles = (UINT)drawList.indices.size();
		}
		void Draw(RfMat33 mat)
		{
			shader.use();
			glBindVertexArray(VAO);
			shader.setMat3("proj", mat.out);
			glDrawElements(GL_TRIANGLES, countTriangles, GL_UNSIGNED_INT, 0);
		}

	};
	float rad = 0;
	RfDrawList drawlist;
	RfGLDrawListRender drawListRender;
	RfVector2 mousev, origin, mousedownv;
	float zoom = 1.f;
	struct camera
	{
		float x, y, rotation, zoom;
	};
	RfVector2 mpos;
public:
	Example2()
	{
		Animate(120);

		//gl
		drawListRender.Init();
	}
protected:
	void AddShape()
	{
		auto rect = new RfRectangle({});
	}
	void OnMouseMove(RfMouseEvent& e)override
	{
		mpos.Set((float)e.x, (float)e.y);
		auto hw = GetWidth() * 0.5f;
		auto hh = GetHeight() * 0.5f;
		auto curr = RfVector2(e.x - hw, hh - e.y);
		if (IsMouseDown()) {
			auto offset = curr - mousev;
			origin += offset;

		}

		mousev = curr;

		auto screen = -origin + curr;
		print("origin x {} y {}\n", origin.x, origin.y);
		print("screen x {} y {}\n", screen.x, screen.y);


	}
	void OnMouseDown(RfMouseEvent& e)override
	{
		auto hw = GetWidth() * 0.5f;
		auto hh = GetHeight() * 0.5f;
		mousedownv.Set(e.x - hw, hh - e.y);
	}
	RfVector2 GetClipPos()
	{
		// get normalized 0 to 1 position across and down canvas
		float normalizedX = mpos.x / (float)GetWidth();
		float normalizedY = mpos.y / (float)GetHeight();

		return {
			normalizedX * 2 - 1,
			normalizedY * -2 + 1
		};
	}
	void OnMouseWheel(RfMouseEvent& e)override
	{
		print("delta {} \n", e.delta);
		if (e.delta == e.SCROLL_DOWN)
		{
			zoom += 0.1f;
		}
		else
		{
			zoom -= 0.1f;

		}

	}
	void OnSize(RfSizeEvent& e)override
	{
		RfGLWindow::OnSize(e);
	}
	void OnPaint() override
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		//update
		{
			drawlist.Clear();
			/*drawlist.Translate(200.f, 20.f);
			drawlist.Rotate(rad);
			drawlist.AddTriangle(20, RfColor::Aqua);*/
			drawlist.AddLine({ -2000,0 }, { 2000,0 }, 0.5, RfColor::Red & 0xffffffaa);
			drawlist.AddLine({ 0,-2000 }, { 0,2000 }, 0.5, RfColor::Red & 0xffffffaa);

			drawlist.AddLine({ 0,0 }, { -100,-100 }, 15, RfColor::Aqua & 0xffffffaa);
			drawlist.AddLine({ 0,0 }, { 100,100 }, 10, RfColor::Blue & 0xffffffaa);

			drawlist.Translate(300, 300);
			drawlist.AddTriangle(50, RfColor::Red);

		}
		//render
		{
			drawListRender.Update(drawlist);

			RfMat33 proj;
			proj.MakeProjection({ (float)GetWidth(),
				(float)GetHeight() });

			proj.Scale({ zoom,zoom });
			proj.Rotate(rad);

			drawListRender.Draw(proj);
		}
		SwapBuffer();
		rad += 0.1f;
	}
};