#include <iostream>
#include <windows.h>
#include <cmath>

const int size = 64;
std::string Products[size]{};
int Products_count[size]{};
int Products_Price[size]{};
int foodIndex = 0, chosee = 0;

int Pokypka(std::string product, int count, int price) {
	if (count <= 0) {
		return 0;
	}
	if (foodIndex >= size) {
		std::cout << "корзина переполнена!\n";
		return 0;
	} 

	if (product == "Боярышник") {
		for (int i = 0; i < foodIndex; i++) {
			if (Products[i] == "Яблочный" ||
				Products[i] == "Апельсиновый" ||
				Products[i] == "Абрикосовый" ||
				Products[i] == "Грушевый") {
				std::cout << "\n\nПокупка настоечки из боярышника заблокирована: в корзине есть фруктовый сок(\n\n";
				Sleep(1500);
				return 0;
			}
		}
	}

	if (product == "Яблочный" ||
		product == "Апельсиновый" ||
		product == "Абрикосовый" ||
		product == "Грушевый") {
		for (int i = 0; i < foodIndex; i++) {
			if (Products[i] == "Боярышник") {
				std::cout << "\n\nДобавление фруктового сока удаляет настоечки боярышника из вашей корзины! Сорян(\n\n";
				Sleep(1500);

				for (int j =i; j < foodIndex - 1; j++) {
					Products[j] = Products[j + 1];
					Products_count[j] = Products_count[j + 1];
					Products_Price[j] = Products_Price[j + 1];
				}
				foodIndex--;
				Products[foodIndex] = "";
				Products_count[foodIndex] = 0;
				Products_Price[foodIndex] = 0;
				break;
			}
		}
	}

	for (size_t i = 0; i < size; i++)
	{
		if (Products[i] == "") {
			Products[i] = product;
			Products_count[i] = count;
			Products_Price[i] = price * count;
			std::cout << Products_count[i] << " " << Products[i] << " за " << Products_Price[i] << "\n";
			foodIndex++;
			return 1;
		}
		else if (Products[i] == product) {
			Products_count[i] += count;
			Products_Price[i] = price * Products_count[i];
			std::cout << Products_count[i] << " " << Products[i] << " за " << Products_Price[i] << "\n";
			return 1;
		}
	}
	return 0;
	
}

int Diskounts() {
	int petrysh = 0, petrysh_price = 0, onion = 0, onion_price = 0;
	int sum = 0;
	for (int i = 0; i < foodIndex; ++i) {
		std::cout << i + 1 << ") " << Products[i] << " x " << Products_count[i]
			<< " = " << Products_Price[i] << "\n";
		sum += Products_Price[i];
	}
	std::cout << "\nИтого без скидок: " << sum << "рублей \n\n";

	for (int i = 0; i < foodIndex; ++i) {
		if (Products[i] == "Петрушевый") {
			petrysh += Products_count[i];
			petrysh_price += Products_Price[i];
		}
		if (Products[i] == "Луковый") {
			onion += Products_count[i];
			onion_price += Products_Price[i];
		}
	
	}

	int discount1 = 0;
	if (petrysh >= 3) {
		discount1 = petrysh_price * 5 / 100;
		std::cout << "Скидка 5% на петрушевый чай (" << petrysh << " л): = "
			<< discount1 << " руб.\n";
	}

	int freeOnion = onion / 4;
	int discount2 = 0;
	if (freeOnion > 0) {
		int onion_discount = onion_price / onion;
		discount2 = freeOnion * onion_discount;
		std::cout << "Подарок: " << freeOnion << " л лукового сока за "
			<< discount2 << " руб бесплатно!\n";
	}

	int after_discounts = sum - discount1 - discount2;

	const int DISCOUNT = 2000;  
	int discount3 = 0;
	if (after_discounts > DISCOUNT) {
		discount3 = after_discounts * 13 / 100;
		std::cout << "Скидка 13% на весь чек  = " << discount3 << " руб.\n";
	}

	if (discount1 == 0 && discount2 == 0 && discount3 == 0) {
		std::cout << "Скидок нет.\n";
	}

	int total = after_discounts - discount3;
	std::cout << "\n----------------------------------\n";
	std::cout << "Итого к оплате: " << total << " руб. \n\n";
	return total;

}

void Korzina() {
	system("cls");
	std::cout << "\t << Ваша корзина >> \n\n";
	if (foodIndex == 0) {
		std::cout << "Корзина пуста( \n";
		Sleep(1400);
	}
	else {
		int delete_product = 0, delete_product_count = 0;
		Diskounts();

		std::cout << "Хотите удалить что-та ? 1 - да, 0 - нет \n";
		std::cin >> chosee;
		if (chosee != 1 && chosee != 0)
		{
			std::cout << "\nНекорректный ввод!";
			Sleep(1200);
			return;
		}
		else if (chosee == 0)
		{
			system("cls");
			std::cout << "----------------------------------\n";
			std::cout << "\t < Ваш заказ >\n";
			std::cout << "----------------------------------\n\n";
			
			Diskounts();
			std::cout << "Спасибо за заказ у нас! Ждем вас снова) \n\n";
			system("pause");
		}
		else 
		{
			while (true)
			{
				system("cls");
				std::cout << "----------------------------------\n";
				std::cout << "\t < Удаление >\n";
				std::cout << "----------------------------------\n\n";
				
				Diskounts();

				std::cout << "\nВыберите номер позиции для удаления: ";
				std::cin >> delete_product;
				if (delete_product < 1 || delete_product > foodIndex) {
					std::cout << "Неверный номер позиции!\n";
					Sleep(1200);
					continue;
				}

				std::cout << "\nВведите кол-во продукта для удаления: ";
				std::cin >> delete_product_count;
				if (delete_product_count > Products_count[delete_product - 1] || delete_product_count < 0)
				{
					std::cout << "\nНекорректное кол-во продукта!\n";
					Sleep(1200);
					continue;
				}


				std::cout << "\nВы действительно хотите удалить " << delete_product << ") " << Products[delete_product - 1] << " " << delete_product_count
					<< " шт за " << Products_Price[delete_product - 1] << "? \n";
				std::cout << "1 - да, 0 - нет \n";
				std::cin >> chosee;
				if (chosee != 1 && chosee != 0)
				{
					std::cout << "\nНекорректный ввод!";
					Sleep(1200);
					return;
				}
				else if (chosee == 0)
				{
					std::cout << "\nУдаление отменено\n";
					Sleep(1200);
					return;
				}
				else
				{
					Products_count[delete_product - 1] -= delete_product_count;
					Products_Price[delete_product - 1] = Products_count[delete_product - 1] * (Products_Price[delete_product - 1] / (Products_count[delete_product - 1] + delete_product_count));

					if (Products_count[delete_product - 1] == 0) {
						for (int i = delete_product - 1; i < foodIndex - 1; ++i) {
							Products[i] = Products[i + 1];
							Products_count[i] = Products_count[i + 1];
							Products_Price[i] = Products_Price[i + 1];
						}
						foodIndex--;
						Products[foodIndex] = "";
						Products_count[foodIndex] = 0;
						Products_Price[foodIndex] = 0;
					}

					std::cout << "успешно удалено\n";
					Sleep(1200);
					return;
				}
			}
			
			

		}
	}
}




int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	srand(time(NULL));

	const int size1 = 4;
	const int size2 = 3;
	const int size3 = 2;
	const int size4 = 1;
	std::string fruit[size1]{ "Яблочный", "Апельсиновый", "Абрикосовый", "Грушевый" };
	int fruit_price[size1]{ 80, 90, 90, 85 };
	std::string vegetable[size2]{ "Томатный", "Луковый", "Огуречный" };
	int vegetable_price[size2]{ 95, 110, 110 };
	std::string tea[size3]{ "Чесночный", "Петрушевый" };
	int tea_price[size3]{ 130, 130 };
	std::string nastoyki[size4]{ "Боярышник" };
	int nastoyki_price[size4]{ 1000 };

	int countProducts, choseKategory, choseVkysFruit, count;

	while (true)
	{
		system("cls");
		std::cout << " ________________________________________________ \n";
		std::cout << "|\t\t\t\t\t\t |\n";
		std::cout << " \t << Магазин Соки Вихтории >> \t\t \n";
		std::cout << "|________________________________________________| \n\n";

		std::cout << "Наш Ассортимент: \n";
		std::cout << "1) Фруктовые соки (Яблочный, Апельсиновый, Абрикосовый, Грушевый)\n";
		std::cout << "2) Овощные соки ( Томатный, Луковый, Огуречный)\n";
		std::cout << "3) Чаи (Чесночный, Петрушевый)\n";
		std::cout << "4) Настоечки (Боярышник)\n\n";
		std::cout << "5) Ваша корзина\n\n";

		std::cout << "Выберите категорию из представленных: ";
		std::cin >> choseKategory;
		if (choseKategory < 1 || choseKategory > 5)
		{
			std::cout << "\n Некорректный ввод \n";
			Sleep(800);
		}
		else if (choseKategory == 1)
		{
			while (true)
			{
				system("cls");
				std::cout << "Выбрана категория 1) Фруктовые соки \n";
				std::cout << "Вкусы и цены фруктовых соков: \n";
				for (size_t i = 1; i <= size1; i++)
				{
					std::cout << i << " - " << fruit[i - 1] << " за " << fruit_price[i - 1] << "\n";
				}
				std::cout << "\nДля выхода в главное меню введите 0 \n\n";
				std::cout << "Выберите вкус из представленных: ";
				std::cin >> choseVkysFruit;
				if (choseVkysFruit != 0 && choseVkysFruit != 1 && choseVkysFruit != 2 && choseVkysFruit != 3 && choseVkysFruit != 4)
				{
					std::cout << "\n Некорректный ввод \n";
					Sleep(1200);
				}
				if (choseVkysFruit == 0)
				{
					break;
				}
				else if (choseVkysFruit == 1)
				{
					std::cout << "Ваш выбор: " << fruit[0] << "\n";
					std::cout << "Введите кол-во банок сока для покупки: ";
					std::cin >> count;
					if (Pokypka(fruit[0], count, fruit_price[0]) == 1) {
						std::cout << "\nСок добавлен в корзину! \n";
						Sleep(1200);
					}
				}
				else if (choseVkysFruit == 2)
				{
					std::cout << "Ваш выбор: " << fruit[1] << "\n";
					std::cout << "Введите кол-во банок сока для покупки: ";
					std::cin >> count;
					if (Pokypka(fruit[1], count, fruit_price[1]) == 1) {
						std::cout << "\nСок добавлен в корзину! \n";
						Sleep(1200);
					}
				}
				else if (choseVkysFruit == 3)
				{
					std::cout << "Ваш выбор: " << fruit[2] << "\n";
					std::cout << "Введите кол-во банок сока для покупки: ";
					std::cin >> count;
					if (Pokypka(fruit[2], count, fruit_price[2]) == 1) {
						std::cout << "\nСок добавлен в корзину! \n";
						Sleep(1200);
					}
				}
				else if (choseVkysFruit == 4)
				{
					std::cout << "Ваш выбор: " << fruit[3] << "\n";
					std::cout << "Введите кол-во банок сока для покупки: ";
					std::cin >> count;
					if (Pokypka(fruit[3], count, fruit_price[3]) == 1) {
						std::cout << "\nСок добавлен в корзину! \n";
						Sleep(1200);
					}
				}

			}
		}
		else if (choseKategory == 2)
		{
			while (true)
			{
				system("cls");
				std::cout << "Выбрана категория 2) Овощные соки \n";
				std::cout << "Вкусы и цены овощных соков: \n";
				for (size_t i = 1; i <= size2; i++)
				{
					std::cout << i << " - " << vegetable[i - 1] << " за " << vegetable_price[i - 1] << "\n";
				}
				std::cout << "\nДля выхода в главное меню введите 0 \n\n";
				std::cout << "Выберите вкус из представленных: ";
				std::cin >> choseVkysFruit;
				if (choseVkysFruit != 0 && choseVkysFruit != 1 && choseVkysFruit != 2 && choseVkysFruit != 3)
				{
					std::cout << "\n Некорректный ввод \n";
					Sleep(1200);
				}
				if (choseVkysFruit == 0)
				{
					break;
				}
				else if (choseVkysFruit == 1)
				{
					std::cout << "Ваш выбор: " << vegetable[0] << "\n";
					std::cout << "Введите кол-во банок сока для покупки: ";
					std::cin >> count;
					Pokypka(vegetable[0], count, vegetable_price[0]);
					std::cout << "\nСок добавлен в корзину! \n";
					Sleep(1200);
				}
				else if (choseVkysFruit == 2)
				{
					std::cout << "Ваш выбор: " << vegetable[1] << "\n";
					std::cout << "Введите кол-во банок сока для покупки: ";
					std::cin >> count;
					Pokypka(vegetable[1], count, vegetable_price[1]);
					std::cout << "\nСок добавлен в корзину! \n";
					Sleep(1200);
				}
				else if (choseVkysFruit == 3)
				{
					std::cout << "Ваш выбор: " << vegetable[2] << "\n";
					std::cout << "Введите кол-во банок сока для покупки: ";
					std::cin >> count;
					Pokypka(vegetable[2], count, vegetable_price[2]);
					std::cout << "\nСок добавлен в корзину! \n";
					Sleep(1200);
				}

			}
		}
		else if (choseKategory == 3)
		{
			while (true)
			{
				system("cls");
				std::cout << "Выбрана категория 3) Чаи \n";
				std::cout << "Вкусы и цены чая: \n";
				for (size_t i = 1; i <= size3; i++)
				{
					std::cout << i << " - " << tea[i - 1] << " за " << tea_price[i - 1] << "\n";
				}
				std::cout << "\nДля выхода в главное меню введите 0 \n\n";
				std::cout << "Выберите вкус из представленных: ";
				std::cin >> choseVkysFruit;
				if (choseVkysFruit != 0 && choseVkysFruit != 1 && choseVkysFruit != 2 && choseVkysFruit != 3)
				{
					std::cout << "\n Некорректный ввод \n";
					Sleep(1200);
				}
				if (choseVkysFruit == 0)
				{
					break;
				}
				else if (choseVkysFruit == 1)
				{
					std::cout << "Ваш выбор: " << tea[0] << "\n";
					std::cout << "Введите кол-во банок для покупки: ";
					std::cin >> count;
					Pokypka(tea[0], count, tea_price[0]);
					std::cout << "\nЧай добавлен в корзину! \n";
					Sleep(1200);
				}
				else if (choseVkysFruit == 2)
				{
					std::cout << "Ваш выбор: " << tea[1] << "\n";
					std::cout << "Введите кол-во банок чая для покупки: ";
					std::cin >> count;
					Pokypka(tea[1], count, tea_price[1]);
					std::cout << "\nЧай добавлен в корзину! \n";
					Sleep(1200);
				}

			}
		}
		else if (choseKategory == 4)
		{
			while (true)
			{
				system("cls");
				std::cout << "Выбрана категория 4) Настоечки \n";
				std::cout << "Вкусы и цены настоечек: \n";
				for (size_t i = 1; i <= size4; i++)
				{
					std::cout << i << " - " << nastoyki[i - 1] << " за " << nastoyki_price[i - 1] << "\n";
				}
				std::cout << "\nДля выхода в главное меню введите 0 \n";
				std::cout << "Выберите вкус из представленных: ";
				std::cin >> choseVkysFruit;
				if (choseVkysFruit != 0 && choseVkysFruit != 1 && choseVkysFruit != 2 && choseVkysFruit != 3)
				{
					std::cout << "\n Некорректный ввод \n";
					Sleep(1200);
				}
				if (choseVkysFruit == 0)
				{
					break;
				}
				else if (choseVkysFruit == 1)
				{
					std::cout << "Ваш выбор: " << nastoyki[0] << "\n";
					std::cout << "Введите кол-во банок настойки для покупки: ";
					std::cin >> count;
					if (Pokypka(nastoyki[0], count, nastoyki_price[0]) == 1) {
						std::cout << "\nНастоечка добавлена в корзину! \n";
						Sleep(1200);
					}
				}

			}
		}
		else if (true)
		{
		
			system("cls");
			Korzina();
	
		}
	}

	return 0;
}










