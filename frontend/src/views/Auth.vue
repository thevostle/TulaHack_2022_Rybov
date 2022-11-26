<template>
	<div class="registrationPage">
		<div class="registrationPage__column">
			<div class="registrationPage__registrationWrapper">
				<h1 class="registrationPaage__title">{{ isLogin ? 'Вход' : 'Регистрация' }}</h1>
				<span class="registrationPage__entranceText">
					{{ isLogin ? 'У меня нет аккаунта. ' : 'У меня уже есть аккаунт. ' }}
				</span>
				<span class="registrationPage__entrance" @click="switchIsLogin">
					{{ isLogin ? 'Зарегистрироваться' : 'Войти' }}
				</span>
				<form @submit.prevent="sendData">
					<div class="registrationPage__inputWrapper">
						<p class="registrationPage__description">Имя пользователя</p>
						<input
							type="text"
							class="registrationPage__input"
							placeholder="Имя пользователя"
							name="username"
							v-model="username"
						/>
					</div>
					<div class="registrationPage__inputWrapper" v-if="!isLogin">
						<p class="registrationPage__description">Адрес электронной почты</p>
						<input
							type="email"
							class="registrationPage__input"
							:class="isLogin ? 'hideOnDesktop' : ''"
							placeholder="Адрес электронной почты"
							name="email"
							v-model="email"
						/>
					</div>
					<div class="registrationPage__inputWrapper">
						<div class="registrationPage__descriptionContainer">
							<p class="registrationPage__description">Пароль</p>
							<p :class="registrationPage__forgotPassword" v-if="!isLogin">Забыли пароль?</p>
						</div>
						<input
							type="password"
							class="registrationPage__input registrationPage__input_bottom"
							name="password"
							placeholder="Пароль"
							v-model="password"
						/>
					</div>
					<div class="registrationPage__checkboxWrapper">
						<input
							type="checkbox"
							name="remember"
							class="registrationPage__checkbox"
							checked="{isRemember}"
							@click="switchIsRemember"
						/>
						<p class="registrationPage__description_checkbox">Запомнить меня</p>
					</div>
					<div class="registrationPage__buttonWrapper">
						<button type="submit" class="registrationPage__button">
							<div class="registrationPage__buttonText">
								{{ isLogin ? 'Войти' : 'Зарегистрироваться' }}
							</div>
							<img :src="imgArrow" class="registrationPage__buttonImage" type="submit" />
						</button>
					</div>
				</form>
			</div>
		</div>
	</div>
</template>

<script>
import imgArrow from '../assets/images/pages/pageAuth/arrow.png';

export default {
	data() {
		return {
			username: '',
			email: '',
			password: '',

			isRemember: false,
			isLogin: false,

			imgArrow: imgArrow,
		};
	},
	methods: {
		switchIsLogin() {
			this.isLogin = !this.isLogin;
		},
		switchIsRemember() {
			this.isRemember = !this.isRemember;
		},
		async sendData() {
			const apiUrl = 'https://72e1-94-28-235-94.eu.ngrok.io/';
			const action = 'users/login';

			const requestOptions = {
				method: 'POST',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify({ login: 'testUser', password: 'testPassword' }),
			};
			const response = await fetch(`${apiUrl}${action}`, requestOptions);
			const data = await response.json();
			console.log(data);
		},
	},
};
</script>

<style lang="scss">
@mixin desktop {
	@media (max-width: 120rem) {
		@content;
	}
}

@mixin laptops {
	@media (max-width: 98rem) {
		@content;
	}
}

@mixin tablets {
	@media (max-width: 76.8rem) {
		@content;
	}
}

@mixin phones {
	@media (max-width: 32rem) {
		@content;
	}
}

$commonWhite: #ffffff;
$uncommonWhite: #fafafa;
$commonBlack: #000000;
$commonGray: #333333;
$darkGray: #181818;
$lightGray: #828282;
$extraLightGray: #f6f6f6;
$lightestGray: #f5f5f5;
$counterStrikeGray: #c4c4c4;
$gray: #4f4f4f;

$lightBlue: #4076ca;
$contrastBlue: #0061ff;
$darkBlue: #114495;
$dullBlue: #e0eafa;

$sand: #ebc750;
$brick: #c84939;
$orange: #fb5a01;
$swampGreen: #0c9d0a;
$lightGreen: #3fc775;

.registrationPage {
	display: flex;
	justify-content: space-around;
	background: $darkGray;
	min-height: 100vh;

	@include tablets {
		flex-direction: column-reverse;
	}
}

.registrationPage__entrance {
	cursor: pointer;
	color: $contrastBlue;

	@include phones {
		display: none;
	}
}

.registrationPage__entranceText {
	@include phones {
		display: none;
	}
}

.registrationPage__column {
	display: flex;
	align-items: center;

	@include tablets {
		justify-content: center;
	}

	&_left {
		width: auto;

		@include phones {
			padding: 0;
		}
	}
}

.registrationPage__registrationWrapper {
	width: 40rem;
	background: $darkGray;

	@include tablets {
		top: -25rem;
		position: relative;
	}

	@include phones {
		width: 100%;
		border-radius: 40px 40px 0 0;
		padding: 2rem;
	}
}

.registrationPage__title {
	font-style: normal;
	font-weight: 400;
	font-size: 2.4rem;
	line-height: 3rem;
	color: $commonWhite;
	margin-bottom: 1.2rem;
}

.registrationPage__label {
	font-style: normal;
	font-weight: 400;
	font-size: 1.4rem;
	line-height: 1.8rem;
	color: $commonWhite;
	margin-bottom: 1.2rem;

	&_checkbox {
		margin-bottom: 0;
	}
}

.registrationPage__descriptionContainer {
	display: flex;
	justify-content: space-between;
}

.registrationPage__description {
	@include phones {
		display: none;
	}
}

.registrationPage__forgotPassword {
	font-style: normal;
	font-size: 1.2rem;
	line-height: 1.4rem;
	letter-spacing: 0.02em;
	color: $lightBlue;

	@include phones {
		display: none;
	}
}

.registrationPage__descriptionRemember {
	@include phones {
		width: 9.3rem;

		font-style: normal;
		font-weight: 400;
		font-size: 0.9rem;
		line-height: 1.1rem;
		display: flex;
		align-items: center;

		color: $gray;
	}
}

.registrationPage__checkboxWrapper {
	display: flex;
	align-items: center;
	margin-bottom: 2rem;
}

.registrationPage__checkbox {
	margin-right: 1.6rem;
	width: 2rem;
	height: 2rem;
	background: $commonWhite;
	border: 1px solid rgba(189, 189, 189, 0.7);
	border-radius: 2px;

	@include phones {
		width: 1.3rem;

		background: $commonWhite;

		border: 0.646067px solid rgba(189, 189, 189, 0.7);
		border-radius: 1.29213px;
	}
}

.registrationPage__button {
	height: 3.5rem;
	background: $contrastBlue;
	border-radius: 7px;
	color: $commonWhite;
	width: 100%;

	@include phones {
		background: none;
		border: none;
		border-radius: 0;

		width: 13rem;
		height: 2.6rem;

		font-style: normal;
		font-weight: 400;
		font-size: 1.3rem;
		line-height: 1.6rem;
		display: flex;
		align-items: center;

		color: $commonBlack;
	}

	&:hover {
		background: $darkBlue;
	}
}

.registrationPage__buttonText {
	@include phones {
		margin-right: 8rem;
	}
}

.registrationPage__buttonImage {
	display: none;
	@include phones {
		display: block;
	}
}

.registrationPage__input {
	width: 100%;
	background: $commonWhite;
	color: $commonBlack;
	border: 1px solid rgba(189, 189, 189, 0.7);
	border-radius: 7px;
	height: 4rem;
	margin-bottom: 2.2rem;
	padding-left: 1.8rem;

	@include laptops {
		margin-bottom: 0.2rem;
	}

	@include phones {
		border: none;
		border-bottom: 1px solid rgba(189, 189, 189, 0.7);
		background: #f9f9f9;
	}
}

.registrationPage__input_bottom {
	@include phones {
		margin: 0 0 1.2rem 0;
	}
}

.registrationPage__image {
	height: 100vh;
}
</style>
