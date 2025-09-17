from engine import create_table, SessionLocal
from model import Artist, Artist_Track, Track
import os
create_table()


def filling(session):
    folder = "Tracks"
    composition_list = list(os.walk(folder))[0][-1]

    use_artist = set()
    use_track = set()

    use_artist_id = {}

    for comp in composition_list:
        artists, track_mp3 = comp.split("~")
        artists = artists.split(", ")
        track = track_mp3.split(".")[0]

        obj_track = None  # для получения id

        artist_id = []

        for artist in artists:
            if (artist not in use_artist):
                obj_artist = Artist(name=artist)
                session.add(obj_artist)
                session.flush()
                use_artist_id[artist] = obj_artist.id
                artist_id.append(obj_artist.id)
                use_artist.add(artist)
            else:
                artist_id.append(use_artist_id[artist])
                
        if (track not in use_track):
            obj_track = Track(name=track, path="Track/" + comp, rating=0)
            session.add(obj_track)
            session.flush()
            use_track.add(track)

        for i in artist_id:
            obj_connection = Artist_Track(artist_id=i, track_id=obj_track.id)
            session.add(obj_connection)


def main():
    with SessionLocal() as session:
        filling(session)
        session.commit()


if __name__ == "__main__":
    main()
