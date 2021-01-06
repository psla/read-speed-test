using System.IO;

namespace ReadSpeedTest
{
    internal class NullStream : Stream
    {
        private long length;
        private long position;

        public NullStream()
        {
        }

        public override bool CanRead => true;

        public override bool CanSeek => false;

        public override bool CanWrite => true;

        public override long Length => length;

        public override long Position { get { return position; } set { throw new System.NotImplementedException(); } }

        public override void Flush()
        {
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            throw new System.NotImplementedException();
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            throw new System.NotImplementedException();
        }

        public override void SetLength(long value)
        {
            throw new System.NotImplementedException();
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            length += count;
            position += count;
        }
    }
}