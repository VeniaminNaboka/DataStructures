#include<iostream>
#include<ctime>
#include<string>
#include<cmath>
#include<corecrt_math_defines.h>
using namespace std;

#define delimiter "\n-------------------------------------\n"

//#define TestShapes

//#define _USE_MATH_DEFINES // for C++ 

//enum Color :short;
enum Color
{
	Red,
	Green,
	Blue,
	Black,
	White,
	Count
};

const char* Colors[] =
{
	"Red",
	"Green",
	"Blue",
	"Black",
	"White"
};

class Shape
{
	Color color;
public:
	Color getColor()
	{
		return this->color;
	}
	void setColor(Color color)
	{
		this->color = color;
	}
	virtual const char* getType()
	{
		return typeid(*this).name();
	}
	Shape(Color color)
	{
		setColor(color);
	}
	virtual void Draw() = 0;		
	virtual double getArea() = 0;
	virtual double getPerimeter() = 0;
	virtual ~Shape() {};
};

class Square :public Shape
{
	double Side;
public:
	double getSide()
	{
		return this->Side;
	}
	void setSide(double Side)
	{
		this->Side = Side;
	}
	char const* getType()
	{
		return typeid(*this).name();
	}
	Square(Color color, double Side = 1) :Shape(color)
	{
		setSide(Side);
	}
	~Square()
	{
		cout << "SqDestructor:\t" << this << endl;
	}
	void Draw() override
	{
		for (int i = 0; i < Side; i++)
		{
			for (int j = 0; j < Side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	double getArea()override
	{
		return Side*Side;
	}
	double getPerimeter()override
	{
		return Side * 4;
	}
};

class Rectangle :public Shape
{
	double Side1;
	double Side2;
public:
	double getSide1()
	{
		return Side1;
	}
	double getSide2()
	{
		return Side2;
	}
	void setSide1(double Side1)
	{
		this->Side1 = Side1;
	}
	void setSide2(double Side2)
	{
		this->Side2 = Side2;
	}
	Rectangle(Color color, double Side1, double Side2) :Shape(color), Side1(Side1), Side2(Side2)
	{
		cout << "RConstructor:\t" << this << endl;
	}
	~Rectangle()
	{
		cout << "RDestructor:\t" << this << endl;
	}
	void Draw()override
	{
		for (int i = 0; i < Side1; i++)
		{
			for (int j = 0; j < Side2; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	double getArea()override
	{
		return Side1*Side2;
	}
	double getPerimeter()
	{
		return (Side1 + Side2) * 2;
	}
};

class Triangle :public Shape
{
	double Base, Side1, Side2;
public:
	void setBase(double Base)
	{
		this->Base = Base;
	}
	void setSide1(double Side1)
	{
		this->Side1 = Side1;
	}
	void setSide2(double Side2)
	{
		this->Side2 = Side2;
	}
	double getBase()
	{
		return this->Base;
	}
	double getSide1()
	{
		return this->Side1;
	}
	double getSide2()
	{
		return this->Side2;
	}
	Triangle(Color color, double Base, double Side1, double Side2) :Shape(color)
	{
		setBase(Base);
		setSide1(Side1);
		setSide2(Side2);
	}
	~Triangle()
	{
		cout << "TriDestructor:\t" << this << endl;
	}

	void Draw()
	{
		for (int i = 0; i < Base; i++)
		{
			for (int j = 0; j < i; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	double getArea()
	{
		double halfPerimeter = getPerimeter()/2;
		double S = sqrt(halfPerimeter*(halfPerimeter-Base)*(halfPerimeter-Side1)*(halfPerimeter-Side2));
		return S;
	}
	double getPerimeter()
	{
		return Base + Side1 + Side2;
	}
};

class Circle :public Shape
{
	double Radius;
public:
	double getRadius()
	{
		return this->Radius;
	}
	void setRadius(double Radius)
	{
		this->Radius = Radius;
	}
	Circle(Color color, double Radius) :Shape(color)
	{
		setRadius(Radius);
	}
	~Circle()
	{
		cout << "CDestructor:\t" << this << endl;
	}

	void Draw() override
	{
		cout << "Поверьте мне, ЭТО КРУГ!!!" << endl;
	}

	double getArea() override
	{
		return M_PI*pow(Radius, 2);
	}

	double getPerimeter()
	{
		return 2 * M_PI*Radius;
	}
};

class ShapeFactory
{
public:
	enum ShapeType { SQUARE, RECTANGLE, TRIANGLE, CIRCLE, Count };
	static Shape* CreateShape(ShapeType type)
	{
		switch (type)
		{
		case SQUARE:	return new Square(Color(rand() % (int)Color::Count), rand() % 10);		break;
		case RECTANGLE:	return new Rectangle(Color(rand() % (int)Color::Count), rand() % 10, rand() % 10); break;
		case TRIANGLE:	return new Triangle(Color(rand() % (int)Color::Count), rand() % 10, rand() % 10, rand() % 10); break;
			throw std::exception("Error: No triangles here! :-(");
		case CIRCLE:	return new Circle(Color(rand() % (int)Color::Count), rand() % 10);	break;
		default:		throw std::exception("Error: No such shape here! :-(");
		}
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef TestShapes
	cout << M_PI << endl;
	Square sq1(Color::Green, 5);
	sq1.Draw();
	cout << "Цвет фигуры:\t" << Colors[sq1.getColor()] << endl;
	cout << "Сторона квадрата: " << sq1.getSide() << endl;
	cout << "Периметр квадрата: " << sq1.getPerimeter() << endl;
	cout << "Площадь квадрата: " << sq1.getArea() << endl;
	cout << (sq1.getType()) << endl;
	std::cout << delimiter << std::endl;

	Rectangle rect1(Color::Blue, 5, 18);
	cout << (rect1.getType()) << endl;
	rect1.Draw();
	cout << "Первая сторона прямоугольника: " << rect1.getSide1() << endl;
	cout << "Вторая сторона прямоугольника: " << rect1.getSide2() << endl;
	cout << "Периметр прямоугольника: " << rect1.getPerimeter() << endl;
	cout << "Площадь прямоугольника: " << rect1.getArea() << endl;
	std::cout << delimiter << std::endl;

	Circle c1(Color::Red, 5);
	cout << (c1.getType()) << endl;
	c1.Draw();
	cout << "Цвет фигуры:\t" << Colors[c1.getColor()] << endl;
	cout << "Радиус круга: " << c1.getRadius() << endl;
	cout << "Периметр круга: " << c1.getPerimeter() << endl;
	cout << "Площадь круга: " << c1.getArea() << endl;
	std::cout << delimiter << std::endl;
#endif // TestShapes

	cout << typeid((int)Color::Count).name() << endl;

	srand(time(NULL));
	int NumberOfShapes = rand() % 5;
	cout << NumberOfShapes << endl;
	Shape** shapes = new Shape*[NumberOfShapes] {};
	try
	{
		for (int i = 0; i < NumberOfShapes; i++)
		{
			shapes[i] = ShapeFactory::CreateShape(ShapeFactory::ShapeType(rand() % (int)ShapeFactory::ShapeType::Count));
		}

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	
	for (int i = 0; i < NumberOfShapes; i++)
	{
		shapes[i]->Draw();
		cout << shapes[i]->getType() << endl;
		//cout << typeid(shapes[i]->getColor()).name() << endl;
		cout << Colors[shapes[i]->getColor()] << endl;
		cout << "Площадь:\t" << shapes[i]->getArea() << endl;
		cout << "Периметр:\t" << shapes[i]->getPerimeter() << endl;
	}
}