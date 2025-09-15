from aiogram.fsm.state import StatesGroup, State


class Find_Track_State(StatesGroup):
    artist_name = State()
    track_title = State()
