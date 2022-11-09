#pragma once
class Stock
{
	public:

	Stock();
	Stock(const char* name, Product** products, size_t count);
	~Stock();

	size_t getCount();
	Product** getProducts();
	void setName(const char* name);
	void setProducts(Product** products, size_t length);

	void appendProduct(Product* product);
	void deleteProduct(Product* product);
	void deleteProductById(size_t id);
	Product* getProductById(size_t id);
	void clearProducts();
	void print();

	private:

	char* _name;
	Product** _products;
	size_t _count;
};

Stock::Stock()
{
	_name = nullptr;
	setProducts(nullptr, 0);
}

Stock::Stock(const char* name, Product** products, size_t count)
	:Stock()
{
	setName(name);
	setProducts(products, count);
}

Stock::~Stock()
{
	delete[] _name;
	_name = nullptr;
	for (size_t i = 0; i < _count; i++)
	{
		delete _products[i];
		_products[i] = nullptr;
	}
	delete[] _products;
	_products = nullptr;
}

size_t Stock::getCount() { return _count; }

Product** Stock::getProducts() { return _products; }

void Stock::setName(const char* name)
{
	if (name == nullptr)
		assert(!"Name can't be null");
	if (_name != nullptr)
		delete[] _name;
	size_t len = strlen(name) + 1;
	_name = new char[len];
	strcpy_s(_name, len, name);
}

void Stock::setProducts(Product** products, size_t count)
{
	if (products)
		for (size_t i = 0; i < count; i++)
		{
			for (size_t j = 0; j < count; j++)
			{
				if (i != j && products[i] == products[j])
					assert(!"You can't add two or more same products in the product list");
			}
		}
	if (_products)
	{
		for (size_t i = 0; i < count; i++)
		{
			delete _products[i];
			_products[i] = nullptr;
		}
		delete[] _products;
		_products = nullptr;
	}
	_products = products;
	_count = count;
}

void Stock::appendProduct(Product* product)
{
	if (_products == nullptr)
	{
		_products = new Product * [_count + 1] {product};
		return;
	}
	for (size_t i = 0; i < _count; i++)
	{
		if (_products[i] == product)
			assert(!"Product already exits");
	}
	Product** products = new Product * [_count + 1];
	for (size_t i = 0; i < _count; i++)
	{
		products[i] = _products[i];
	}
	products[_count] = product;
	_count++;
	delete[] _products;
	_products = products;
}

void Stock::deleteProduct(Product* product)
{
	if (_products == nullptr)
		assert(!"Product not exits");
	bool temp = true;
	for (size_t i = 0; i < _count; i++)
	{
		if (_products[i] == product)
		{
			temp = false;
			delete _products[i];
			_products[i] = nullptr;
			break;
		}
	}
	if (temp)
		assert(!"Product not exits");
	Product** products = new Product * [_count - 1];
	for (size_t i = 0; i < _count - 1; i++)
	{
		if (_products[i] == nullptr)
			temp = 1;
		products[i] = _products[i + temp];
	}
	_count--;
	delete[] _products;
	_products = products;
}

void Stock::deleteProductById(size_t id)
{
	if (_products == nullptr)
		assert(!"Product not exits");
	for (size_t i = 0; i < _count; i++)
	{
		if (_products[i]->getId() == id)
			return deleteProduct(_products[i]);
	}
}

Product* Stock::getProductById(size_t id)
{
	if (_products == nullptr)
		assert(!"Product not exits");
	for (size_t i = 0; i < _count; i++)
	{
		if (_products[i]->getId() == id)
			return _products[i];
	}
	assert(!"Product not exits");
}

void Stock::clearProducts()
{
	if (_products == nullptr)
		return;
	for (size_t i = 0; i < _count; i++)
	{
		delete _products[i];
		_products[i] = nullptr;
	}
	delete[] _products;
	_products = nullptr;
	_count = 0;
}

void Stock::print()
{
	cout << "===============================" << '\n';
	cout << "Stock name: " << (_name ? _name : "None") << '\n';
	for (size_t i = 0; i < _count; i++)
	{
		_products[i]->print();
	}
	cout << "===============================" << '\n';
}