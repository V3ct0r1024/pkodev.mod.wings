# pkodev.mod.wings / Эффект полета для крыльев

![Эффект полета](https://raw.githubusercontent.com/V3ct0r1024/pkodev.mod.wings/master/img/3.png)

Данная модификация [**pkodev.mod.loader**](https://github.com/V3ct0r1024/pkodev.mod.loader) для клиента MMORPG-игры "Tales of Pirates (рус. "Пиратия") позволяет добавлять к любым **Крыльям** (предметы с типом **44**) **эффект полета**, аналогичный эффекту **Крыльев перерождения**.

## Информация о модификации 

-   **Название:**  pkodev.mod.wings;
-   **Версия:**  1.1;
-   **Автор:**  [V3ct0r](https://github.com/V3ct0r1024);
-   **Тип:**  для игрового клиента (Game.exe);
-   **Поддерживаемые исполняемые файлы (.exe):**  GAME_13X_0, GAME_13X_1, GAME_13X_2, GAME_13X_3, GAME_13X_4, GAME_13X_5.

## Установка и настройка модификации

1. Установите систему загрузки модов [**pkodev.mod.loader**](https://github.com/V3ct0r1024/pkodev.mod.loader), если она не была установлена ранее.
2. Поместите файл DLL-библиотеки мода **[pkodev.mod.wings.client.13x_{ID}.dll](https://github.com/V3ct0r1024/pkodev.mod.wings/releases/)** для Вашей версии Game.exe и файл настроек мода **[pkodev.mod.wings.cfg](https://github.com/V3ct0r1024/pkodev.mod.wings/blob/master/cfg/pkodev.mod.wings.cfg)** в папку **mods\pkodev.mod.wings** игрового клиента.
3. Откройте файл настроек мода **pkodev.mod.wings.cfg** и запишите в него список ID крыльев, к которым необходимо применить эффект полета. Каждый ID записывается с новой строки, например:

		935
		936
		937 
	В результате эффект полета будет применен к **Эльфийским крыльям**, **Крыльям бабочки** и **Ангельским крыльям** соответственно.
4. Установка модификации завершена! Запустите игровой клиент и убедитесь, что модификация работает.

## Обсуждение на форуме PKOdev.NET
 - [Русскоязычный раздел](https://pkodev.net/topic/6006-%D1%8D%D1%84%D1%84%D0%B5%D0%BA%D1%82-%D0%BF%D0%BE%D0%BB%D0%B5%D1%82%D0%B0-%D0%B4%D0%BB%D1%8F-%D0%BA%D1%80%D1%8B%D0%BB%D1%8C%D0%B5%D0%B2/)
 - [Англоязычный раздел](https://pkodev.net/topic/6008-flying-effect-for-wings/)
 
## Полезные ссылки
1. [Бинарные файлы модификации для клиента (.dll)](https://github.com/V3ct0r1024/pkodev.mod.wings/releases)
2. [Файл с настройками модификации для клиента (pkodev.mod.wings.cfg)](https://github.com/V3ct0r1024/pkodev.mod.wings/blob/master/cfg/pkodev.mod.wings.cfg)
3. [Система загрузки модов pkodev.mod.loader](https://github.com/V3ct0r1024/pkodev.mod.loader)