#pragma once
class Product
{
	public:

	Product();
	Product(const char* name, const char* description, double price, short discount);
	~Product();

	size_t getId();
	char* getName();
	char* getDescription();
	double getPrice();
	short getDiscount();

	void setName(const char* name);
	void setDescription(const char* description);
	void setPrice(double price);
	void setDiscount(short discount);

	void print();

	private:

	static size_t _staticId;
	size_t _id;
	char* _name;
	char* _description;
	double _price;
	short _discount;
};

size_t Product::_staticId = 0;

Product::Product()
{
	_name = nullptr;
	_description = nullptr;
	_price = 0;
	_discount = 0;
}

Product::Product(const char* name, const char* description, double price, short discount)
	:Product()
{
	setName(name);
	setDescription(description);
	setPrice(price);
	setDiscount(discount);
}

Product::~Product()
{
	delete[] _name;
	_name = nullptr;
	delete[] _description;
	_description = nullptr;
}

size_t Product::getId() { return _id; }
char* Product::getName() { return _name; }
char* Product::getDescription() { return _description; }
double Product::getPrice() { return _price; }
short Product::getDiscount() { return _discount; }

void Product::setName(const char* name)
{
	if (name == nullptr)
		assert(!"Name can't be null");
	if (_name != nullptr)
		delete[] _name;
	size_t len = strlen(name) + 1;
	_name = new char[len];
	strcpy_s(_name, len, name);
}

void Product::setDescription(const char* description)
{
	if (description == nullptr)
		assert(!"Description can't be null");
	if (_description != nullptr)
		delete[] _description;
	size_t len = strlen(description) + 1;
	_description = new char[len];
	strcpy_s(_description, len, description);
}

void Product::setPrice(double price)
{
	_price = price;
}

void Product::setDiscount(short discount)
{
	if (0 <= discount && discount <= 100)
		_discount = discount;
	assert(!"dicount error");
}

void Product::print()
{
	cout << "===============================" << '\n';
	cout << "Name: " << (_name ? _name : "None") << '\n';
	cout << "Description: " << (_description ? _description : "None") << '\n';
	cout << "Price: " << _price << '\n';
	cout << "Discount: " << _discount << '\n';
	cout << "===============================" << '\n';
}