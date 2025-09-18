from aiogram import Router
from aiogram.types import Message
from FSM.FSM_find import Find_Track_State
from aiogram.fsm.context import FSMContext
from aiogram.filters import Command, CommandObject
from DataBase.engine import SessionLocal
from DataBase.query import get_track, get_artist

router_user = Router()


@router_user.message(Command("artist"))
async def artist_fnd(message: Message, command: CommandObject):
    if (command.args):
        artist_name = command.args
        with SessionLocal() as session:
            result = get_artist(session, artist_name)
            tracks = ""
            for m in result:
                t = m[0] + '\n'
                tracks += t
            await message.answer(f"""There are 5 most popular {artist_name}'s tracks:\n{tracks}""")
    else:
        await message.answer("Введите исполнителя: /artist имя исполнителя")


@router_user.message(Command("track"))
async def track_fnd(message: Message, command: CommandObject):
    if (command.args):
        track_name = command.args
        with SessionLocal() as session:
            result = get_track(session, track_name)
            await message.answer(result[0])
    else:
        await message.answer("Введите название трека: /track название трека")


@router_user.message(Command("search"))
async def deep_search_one(message: Message, state: FSMContext):
    await message.answer("Введите исполнителя")
    await state.set_state(Find_Track_State.artist_name)


@router_user.message(Find_Track_State.artist_name)
async def deep_search_two(message: Message, state: FSMContext):
    await state.update_data(artist_name=message.text)
    await message.answer("Введите название трека")
    await state.set_state(Find_Track_State.track_title)


@router_user.message(Find_Track_State.track_title)
async def deep_search_two(message: Message, state: FSMContext):
    await state.update_data(track_title=message.text)
    data = await state.get_data()
    await message.answer(f"Получено следующая информация\nАртист: {data['artist_name']}\nНазвание: {data['track_title']}")
    await state.set_state(None)
    await state.clear()
