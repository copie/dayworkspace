class Codec:
    def __init__(self):
        self.map = {}

    def encode(self, longUrl):
        """Encodes a URL to a shortened URL.
        
        :type longUrl: str
        :rtype: str
        """
        self.map[str(hash(longUrl))] = longUrl
        return hash(longUrl)

    def decode(self, shortUrl):
        """Decodes a shortened URL to its original URL.
        
        :type shortUrl: str
        :rtype: str
        """
        return self.map[shortUrl]
