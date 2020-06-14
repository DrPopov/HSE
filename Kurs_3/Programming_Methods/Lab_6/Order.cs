using System;
using System.Collections.Generic;
using System.Text;

namespace laba6
{
    public class Order
    {
        public string Number { get; set; }

        public string Code { get; private set; }

        public int Count { get; private set; }

        public string ClientNumber { get; private set; }

        public Order(int count, ClientType type) {
            Code = Guid.NewGuid().ToString();
            Count = count;
            Random rand = new Random();
            if (type == ClientType.Foreigner)
                ClientNumber = $"FN-{rand.Next(10000, 99999)}";
            else if (type == ClientType.Partner)
                ClientNumber = $"PT-{rand.Next(10000, 99999)}";
            else
                ClientNumber = $"NM-{rand.Next(10000, 99999)}";
        }
    }
}
