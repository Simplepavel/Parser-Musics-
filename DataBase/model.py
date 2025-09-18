from sqlalchemy.orm import declarative_base
from sqlalchemy import Column, String, Integer, ForeignKey

Base = declarative_base()


class Artist(Base):
    __tablename__ = "artist"

    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(64))

    def __repr__(self):
        return f"Artist: {self.name} ID: {self.id}"


class Track(Base):
    __tablename__ = "track"

    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(64))
    path = Column(String(512))
    rating = Column(Integer)

    def __repr__(self):
        return f"Track title: {self.name} ID: {self.id} Path: {self.path} Rating: {self.rating}"


class Artist_Track(Base):
    __tablename__ = "artist_track"

    artist_id = Column(Integer, ForeignKey("artist.id"), primary_key=True)
    track_id = Column(Integer, ForeignKey("track.id"), primary_key=True)


