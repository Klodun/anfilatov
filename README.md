# Вариант 1. Теплица

Курсовой проект по ПМ.02 «Сопровождение и схемотехническое обслуживание интеллектуальных интегрированных систем».
Тема: «Разработка и сопровождение виртуальной системы сбора и учёта данных на Arduino». Специальность 09.02.08.

Автор: Анфилатов Ярик Дмитриевич, группа 54-15.
Руководители: Борисов Е.Н., Дадаев М.В.

## Входные данные

| № | Сценарий | Датчик 1 (аналоговый) | Датчик 2 | Датчик 3 | Исполнительное устройство | LED / период T | Порог события |
|---|----------|-----------------------|----------|----------|---------------------------|----------------|---------------|
| 1 | Теплица | NTC (температура воздуха, 0–50 °C) | DHT22 (влажность воздуха) | POT (влажность почвы, 0–100 %) | реле (насос) | красный, 10 мА / 1 с | влажность почвы < 30 % |

## Ссылка на проект Wokwi

https://wokwi.com/projects/478612476002839553

## Файлы

| Файл | Назначение |
|------|-----------|
| [firmware/variant_01/variant_01.ino](firmware/variant_01/variant_01.ino) | скетч Arduino |
| [sim/diagram.json](sim/diagram.json), [sim/sketch.ino](sim/sketch.ino), [sim/libraries.txt](sim/libraries.txt) | файлы проекта Wokwi |
| [db/schema.sql](db/schema.sql), [db/queries.sql](db/queries.sql) | таблицы `readings` и `events`, контрольные запросы |
| [nodered/flow.json](nodered/flow.json), [nodered/function_parse.js](nodered/function_parse.js) | поток Node-RED (разбор лога, контроль диапазонов, загрузка в базу) |
| [data/log.txt](data/log.txt), [data/log_fault.txt](data/log_fault.txt) | журнал штатного сценария и тестовый журнал с неисправностью |
| [start-nodered.bat](start-nodered.bat), [env.bat](env.bat) | запуск Node-RED и командной строки с портативными программами |
| [docs/Курсовая_Анфилатов_вариант1.docx](docs/%D0%9A%D1%83%D1%80%D1%81%D0%BE%D0%B2%D0%B0%D1%8F_%D0%90%D0%BD%D1%84%D0%B8%D0%BB%D0%B0%D1%82%D0%BE%D0%B2_%D0%B2%D0%B0%D1%80%D0%B8%D0%B0%D0%BD%D1%821.docx), [docs/Курсовая_Анфилатов_вариант1.pdf](docs/%D0%9A%D1%83%D1%80%D1%81%D0%BE%D0%B2%D0%B0%D1%8F_%D0%90%D0%BD%D1%84%D0%B8%D0%BB%D0%B0%D1%82%D0%BE%D0%B2_%D0%B2%D0%B0%D1%80%D0%B8%D0%B0%D0%BD%D1%821.pdf) | пояснительная записка |
| [docs/Презентация_Анфилатов_вариант1.pptx](docs/%D0%9F%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%82%D0%B0%D1%86%D0%B8%D1%8F_%D0%90%D0%BD%D1%84%D0%B8%D0%BB%D0%B0%D1%82%D0%BE%D0%B2_%D0%B2%D0%B0%D1%80%D0%B8%D0%B0%D0%BD%D1%821.pptx), [docs/Речь_к_презентации.docx](docs/%D0%A0%D0%B5%D1%87%D1%8C_%D0%BA_%D0%BF%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%82%D0%B0%D1%86%D0%B8%D0%B8.docx) | презентация и речь |
| [docs/user_instruction.md](docs/user_instruction.md), [docs/test_report.md](docs/test_report.md) | инструкция пользователя, журнал тестов |
| [docs/easyeda/](docs/easyeda) | материалы EasyEDA: `SCH_теплица_2026-11-02.json`, `schematic_sheet.pdf`, `specification.pdf`, `bom.csv` |
| [docs/structure.png](docs/structure.png), [docs/algorithm.png](docs/algorithm.png), [docs/er.png](docs/er.png), [docs/shots/](docs/shots) | структурная схема, алгоритм, ER-диаграмма, скриншоты |
| `archive/anfilatov_v1.0.zip` | архив проекта |

`db/variant.db` и `db/load.sql` создаются автоматически при загрузке лога и в репозиторий не входят (`.gitignore`).

## Порядок запуска

1. Запустить `start-nodered.bat`, открыть http://localhost:1880, импортировать `nodered/flow.json` (меню ≡ → Import), нажать Deploy.
2. Открыть проект Wokwi, запустить симуляцию, скопировать вывод Serial Monitor в `data/log.txt`, сохранить файл. Flow сам разберёт лог и загрузит данные в `db/variant.db`.
3. Проверить данные: `sqlite3 db\variant.db ".read db\queries.sql"`.
4. Проверка неисправности: заменить содержимое `data/log.txt` строкой из `data/log_fault.txt`, сохранить; в таблице `events` появится событие `FAULT`.
