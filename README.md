# Сканер мультимедийных файлов

Консольное приложение на C++17 для Linux, которое периодически сканирует файловую систему, ищет мультимедийные файлы и передает актуальный отчет через встроенный HTTP-сервер.

*Автор* - **Соколов Никита**

---

## Описание

Приложение использует POSIX API и открытую библиотеку парсинга JSON-файлов `nlohmann/json`

Используемые расширения мультимедийных файлов находятся в файле `multimedia_extensions.json`

---

## Требования
- Linux
- Компилятор C++17: GCC 7-8 / Clang 5
- CMake
- git

---

## Сборка
```bash
cmake -S . -B build
cmake --build build
```

*При первой конфигурации CMake автоматически скачает и соберёт nlohmann/json через FetchContent*

---

## Запуск
```bash
    ./build/src/scanner <interval> <dir_path>
```
Где `<interval>` - интервал проверки в секундах, а `<dir_path>` - путь сканируемой директории (абсолютный или относительный)

Пример запуска: `./build/src/scanner 30 ~`



### HTTP Server

После запуска сервер доступен по адресу `http://localhost:1234`

Файл с результами обхода находится по адресу `http://localhost:1234/media_files`

Пример сохранения данных сервера в файл:
```bash
curl -o media_files.json http://localhost:1234/media_files
```

Или через запрос (например, в `telnet`): `GET /media_files`


Пример ответа:
```json
{
  "audio": ["/path/to/track.mp3", "/path/to/voice.wav"],
  "video": ["/path/to/myvideo.mp4"],
  "images": ["/path/to/photo.jpg", "/path/to/logo.png"]
}
```

