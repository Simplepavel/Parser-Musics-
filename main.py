from aiogram import Bot, Dispatcher
from dotenv import load_dotenv, find_dotenv
from BotCmd import bot_cmd
from Handlers.user import router_user
import os
import asyncio
load_dotenv(find_dotenv())
bot = Bot(token=os.getenv("TOKEN_BOT"))
dp = Dispatcher()




async def main():
    await bot.set_my_commands(bot_cmd)
    dp.include_routers(router_user)
    await dp.start_polling(bot)

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("Bot has been finished")
