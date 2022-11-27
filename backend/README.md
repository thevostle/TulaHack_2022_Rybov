## Поднятие бэкенда

Наш способ - открытие на локальной машине портов `:5173` и `:8080` при помощи `ngrok`.
Порт `5173` используется для обращения к фронтенду на Vite, а `:8080` для передачи HTTP-запросов на бэк.
В таком случае доменом сайта будет адрес, выданный ngrok на порт `5173`, а с фронтэнда запросы будут передаваться
на домен, выданный на порт `8080`.

## API

Note: Вместо ngrok.back.adress.io должен быть backend-адрес, выданный `ngrok` при прокидывании портов.

## User Controller:

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
    "additional": {
        "login": "login",
        "id": 0
    }
}
```

### Authentification
```
URL: http://ngrok.back.adress.io/user/login
POST: string login, integer password
```

### Get user by ID
```
URL: http://ngrok.back.adress.io/user/get/by_id?id={1}
POST: NONE
```

### Get user by name (login)
```
URL: http://ngrok.back.adress.io/user/get/by_name?name={1}
POST: NONE
```

Server response:
```json
{
    "rybCode": 0,
    "message": "message",
    "additional": {
        "login": "login"
    }
}
```

## Content Controller:

### Fetch all movies
```
URL: http://ngrok.back.adress.io/content/fetch
POST: NONE
```

Server response:
```json
{
    "rybCode": 0,
    "message": "message",
    "additional": {
        "movies": [
            {
                "id": 0,
                "name": "name",
                "rate": 0.000,
                "poster_url": "url",
                "year": 0,
                "genresIds": [
                    0,
                    1,
                ]
            },
        ]
    }
}
```

### Fetch all genres
```
URL: http://ngrok.back.adress.io/genres/fetch
POST: NONE
```

Server response:
```json
{
    "additional": {
        "genres": [
            {
                "id": 1,
                "name": "Horror",
                "rus_name": "Ужасы"
            },
        ]
    },
    "message": "Genres fetched",
    "rybCode": 0
}
```

### Get movie by id
```
URL: http://ngrok.back.adress.io/content/get?id={1}
POST: integer id
```

Server response:
```json
{
    "additional": {
        "name": "Морской бой",
        "poster_url": "https://lf21.lordfilm.lu/uploads/posts/2020-06/466844_1593289203.jpg",
        "rate": 10,
        "year": 2012
    },
    "message": "Movie fetched",
    "rybCode": 0
}
```

## User Rates Controller

### Fetch all movies, rated by user
```
URL: http://ngrok.back.adress.io/user/{userId}/rates/fetch
POST: NONE
```

Server response:
```json
{
    "rybCode": 0,
    "message": "message",
    "additional": {
        "ratedMovies": [
            {
                "movieId": 0,
                "userRate": 0.000,
            },
        ]
    }
}
```

### Add user rate
```
URL: http://ngrok.back.adress.io/user/{userId}/rates/fetch
POST: NONE
```

Server response:
```json
{
    "rybCode": 0,
    "message": "message",
    "additional": {}
}
```

### Update user rate
```
URL: http://ngrok.back.adress.io/user/{userId}/rates/fetch
POST: NONE
```

Server response:
```json
{
    "rybCode": 0,
    "message": "message",
    "additional": {}
}
```