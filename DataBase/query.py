from DataBase.model import Track, Artist, Artist_Track
# from sqlalchemy import text


def get_track(session, title):
    id, path = session.query(Track.id, Track.path).filter(Track.name == title).order_by(
        Track.rating.desc()).one()
    result = session.query(Artist.name).join(Artist_Track, Artist.id ==  # ToDo
                                             Artist_Track.artist_id).filter(Artist_Track.track_id == id).all()
    answer = title
    for i in range(len(result)):
        answer += (", " if (i > 0) else "-") + result[i][0]
    return [answer, path]


def get_artist(session, name):
    id_artist = session.query(Artist.id).filter(
        Artist.name == name).one_or_none()
    if (not id_artist):
        return
    result = session.query(Track.name, Track.path).join(Artist_Track, Artist_Track.track_id ==  # ToDo
                                                        Track.id).filter(
        Artist_Track.artist_id == id_artist[0]).order_by(Track.rating.desc()).limit(5)
    return result.all()
