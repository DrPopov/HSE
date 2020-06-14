using System;
using System.Collections.Generic;
using System.Text;

namespace laba6.Handlers
{
    public class ForeignerHandler: Handler
    {
        public override void Handle(Order order) {
            if (order.ClientNumber.StartsWith("FN")) {
                Console.WriteLine("Заказчик - иностранец. Выполняем по особой процедуре!");
                order.Number = "FN-" + Guid.NewGuid().ToString();
            } else {
                if (Successor != null)
                    Successor.Handle(order);
            }
        }
    }
}
