## Поднятие бэкенда

Наш способ - открытие на локальной машине портов `:5173` и `:8080` при помощи `ngrok`.
Порт `5173` используется для обращения к фронтенду на Vite, а `:8080` для передачи HTTP-запросов на бэк.
В таком случае доменом сайта будет адрес ngrok, выданный на порт `5173`, а с фронтэнда запросы будут передаваться
на домен, выданный на порт `8080`.

## API

Note: Вместо ngrok.back.adress.io должен быть backend-адрес, выданный `ngrok` при прокидывании портов.

### Register user
```
URL: http://ngrok.back.adress.io/user/register
POST: string login, integer password
```
Server response:
```json
{
    "rybCode": 0,
    "message": "message",
    "additional": {}
}
```

### Authentification
```
URL: http://ngrok.back.adress.io/user/login
POST: string login, integer password
```

Server response:
```json
{
    "rybCode": 0,
    "message": "message",
    "additional": {}
}
```