import React from "react";

function SellListingItem(imageUrl, imageAlt, fullAddress, price, btnContent) {
  return (
    <div className="card lg:card-side bg-base-100 shadow-xl">
      <figure>
        <img src={imageUrl} alt={imageAlt} />
      </figure>
      <div className="card-body">
        <h2 className="card-title">{fullAddress}</h2>
        <p>{price.toString().replace(/\B(?=(\d{3})+(?!\d))/g, ",")}</p>
        <div className="card-actions justify-end">
          <button className="btn btn-primary">{btnContent}</button>
        </div>
      </div>
    </div>
  );
}

export default SellListingItem;
